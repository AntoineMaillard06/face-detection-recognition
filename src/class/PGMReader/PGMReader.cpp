#include "./PGMReader.hpp"

long face::PGMReader::getFileSize(const std::string &path)
{
    struct stat stat_buf;
    int rc = stat(path.c_str(), &stat_buf);

    return rc == 0 ? stat_buf.st_size : -1;
}