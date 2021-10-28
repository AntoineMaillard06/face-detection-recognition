#include "./Image.hpp"

face::Image::Image(const std::string &path)
{
    face::PGMReader reader;

    reader.process("./BioID.pgm");
}
