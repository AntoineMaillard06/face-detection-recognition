#include "./PGMReader.hpp"

long face::PGMReader::getFileSize(const std::string &path)
{
    struct stat stat_buf;
    int rc = stat(path.c_str(), &stat_buf);

    return rc == 0 ? stat_buf.st_size : -1;
}

face::PGMReader::~PGMReader()
{
    this->freeContent();
}

std::shared_ptr<face::Mat> face::PGMReader::process(const std::string &path)
{
    std::fstream file(path, std::ios::in);
    const long fileSize = face::PGMReader::getFileSize(path);

    std::cout << "File " << path << " has size " << fileSize << " bytes." << std::endl;
    if (this->_content) {
        this->freeContent();
    }
    if (fileSize == -1) {
        throw face::Exception("File is empty or non-existent.");
    }
    if (file.is_open() && fileSize > 0) {
        this->_content = new char[fileSize + 1];
        if (this->_content) {
            this->_content[fileSize] = '\0';
        } else {
            throw face::Exception("Memory allocation error: can't allocate memory.");
        }
        file.seekg(0, std::ios::beg);
        file.read(this->_content, fileSize);
        file.close();
    }
    this->computeHeader();
    return this->_header.is_binary
        ? this->computeBinaryData(this->_header.gray_scales <= 255 ? 1 : 2)
        : this->computeTextData();
}

void face::PGMReader::computeHeader()
{
    const std::regex headerRegExp(HEADER_REGEXP);
    std::smatch headerMatch;
    const std::string content(this->_content);

    if (std::regex_search(content, headerMatch, headerRegExp)) {
        this->_header.is_binary = headerMatch[1] == "P5";
        this->_header.width = std::stoi(headerMatch[2]);
        this->_header.height = std::stoi(headerMatch[3]);
        this->_header.gray_scales = std::stoi(headerMatch[4]);
        std::cout << "Binary? " << this->_header.is_binary << std::endl
            << "Width? " << this->_header.width << std::endl
            << "Height? " << this->_header.height << std::endl
            << "GrayScalesMax? " << this->_header.gray_scales << std::endl;
    } else {
        throw face::Exception("Invalid pgm header.");
    }
}

std::shared_ptr<face::Mat> face::PGMReader::computeBinaryData(const u_char bytesPerPixel)
{
    std::shared_ptr<uint8_t[]> image_data(new uint8_t[4 * this->_header.width * this->_header.height]{0});
    uint32_t index = 0;
    uint8_t gray = 0;

    this->skipHeader(index);
    for (int i = 0, y = 0; i < (this->_header.width * this->_header.height) / bytesPerPixel; i += 1, y += 4, index += bytesPerPixel) {
        gray = static_cast<uint8_t>(bytesPerPixel == 1 ? this->_content[index] : static_cast<u_short>(this->_content[index])) % 255;
        image_data[y] = gray % 255;
        image_data[y + 1] = gray % 255;
        image_data[y + 2] = gray % 255;
        image_data[y + 3] = 255;
    }
    return std::make_shared<face::Mat>(this->_header, image_data);
}

std::shared_ptr<face::Mat> face::PGMReader::computeTextData()
{
    std::shared_ptr<uint8_t[]> image_data(new uint8_t[4 * this->_header.width * this->_header.height]);
    uint32_t index = 0;
    std::string pixel;
    int decal = 0;

    this->skipHeader(index);
    for(; this->_content[index] != '\0' ; index += 1) {
        if (this->_content[index] >= '0' && this->_content[index] <= '9') {
            pixel += this->_content[index];
        } else {
            image_data[decal] = std::stoi(pixel) % 255;
            image_data[decal + 1] = std::stoi(pixel) % 255;
            image_data[decal + 2] = std::stoi(pixel) % 255;
            image_data[decal + 3] = 255;
            pixel.clear();
            decal += 4;
        }
    }
    if (pixel.length() > 0) {
        image_data[decal] = std::stoi(pixel) % 255;
        image_data[decal + 1] = std::stoi(pixel) % 255;
        image_data[decal + 2] = std::stoi(pixel) % 255;
        image_data[decal + 3] = 255;
        pixel.clear();
    }
    return std::make_shared<face::Mat>(this->_header, image_data);
}

void face::PGMReader::skipHeader(uint32_t &index)
{
    uint8_t separatorCount = 0;

    for (index = 0; this->_content && separatorCount < HEADER_ELEM_COUNT; index += 1) {
        if (this->_content[index] == '\n' || this->_content[index] == '\t'
            || this->_content[index] == ' ' || this->_content[index] == '\r') {
            separatorCount += 1;
        }
    }
}

const face::pgm_header_t &face::PGMReader::getHeader() const
{
    return this->_header;
}

void face::PGMReader::freeContent()
{
    if (this->_content != nullptr) {
        delete []this->_content;
    }
}
