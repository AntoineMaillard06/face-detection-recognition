#include "./Image.hpp"

face::Image::Image(const std::string &path)
{
    const long fileSize = face::PGMReader::getFileSize(path);

    std::cout << "File " << path << " has size " << fileSize << " bytes." << std::endl;
    if (fileSize == -1) {
        throw face::Exception("File is empty or non-existent.");
    }
}
