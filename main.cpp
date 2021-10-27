#include "./src/class/Image/Image.hpp"

int main(int ac, char**av)
{
    try {
        face::Image test("./BioID.pgm");
    } catch (face::Exception err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
