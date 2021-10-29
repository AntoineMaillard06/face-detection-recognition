#include "./src/class/Window/Window.hpp"

int main(int ac, char**av)
{
    try {
        face::Window appWindow;
        face::PGMReader imageReader;

        appWindow.loadImage(imageReader.process("./BioID.pgm"));

        appWindow.windowJoin();
    } catch (face::Exception err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
