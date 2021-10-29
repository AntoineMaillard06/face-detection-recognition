#include "./src/class/PGMReader/PGMReader.hpp"

int main(int ac, char**av)
{
    try {
        face::PGMReader imageReader;

        face::Mat test = imageReader.process("./BioID.pgm");
    } catch (face::Exception err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
