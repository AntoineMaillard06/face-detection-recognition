#include <SFML/Window.hpp>

#include "./../Mat/Mat.hpp"

namespace face {
    class Window {
        public:
        Window() {}
        ~Window();
        void addImage(const face::Mat &image);

        private:
        sf::Window window;
        std::vector<face::Mat> images;
    };
};