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

void face::PGMReader::process(const std::string &path)
{
    std::fstream file("./BioID.pgm", std::ios::in);
    const long fileSize = face::PGMReader::getFileSize(path);

    std::cout << "File " << path << " has size " << fileSize << " bytes." << std::endl;
    if (fileSize == -1) {
        throw face::Exception("File is empty or non-existent.");
    }
    if (file.is_open()) {
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
    if (this->_content && fileSize > 0) {
        this->computeHeader();
    }
}

void face::PGMReader::computeHeader()
{
    const std::regex headerRegExp("^(P2|P5)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]");
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

const face::pgm_header_t &face::PGMReader::getHeader() const
{
    return this->_header;
}

void face::PGMReader::freeContent()
{
    if (this->_content) {
        delete []this->_content;
    }
}
