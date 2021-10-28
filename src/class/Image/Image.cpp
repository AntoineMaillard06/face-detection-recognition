#include "./Image.hpp"

face::Image::Image(const std::string &path)
{
    face::PGMReader reader;

    face::Mat test = reader.process("./BioID.pgm");
}
