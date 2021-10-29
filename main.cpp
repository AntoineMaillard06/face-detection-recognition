#include "./src/class/Window/Window.hpp"

int main(int ac, char**av)
{
    try {
        face::Window appWindow;
        face::PGMReader imageReader;

        std::shared_ptr<face::Mat> test = imageReader.process("./BioID.pgm");

        appWindow.loadImage(test);
        appWindow.windowJoin();
    } catch (face::Exception err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
