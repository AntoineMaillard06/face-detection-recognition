#include <SFML/Window.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>

#include "./../PGMReader/PGMReader.hpp"

namespace face {
    class Window {
        public:
        Window();
        ~Window();
        void loadImage(const std::shared_ptr<face::Mat> &image);
        void windowJoin();

        private:
        void windowThread();

        sf::Window _window;
        std::shared_ptr<face::Mat> _image;
        std::thread _windowThread;
        std::atomic_bool _isRunning;
        std::mutex _mtx;
    };
};