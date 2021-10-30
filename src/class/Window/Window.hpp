#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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

        sf::RenderWindow _window;
        sf::Image _sfImage;
        sf::Texture _sfFaceTexture;
        sf::Sprite _sfSprite;
        std::shared_ptr<face::Mat> _image;
        std::thread _windowThread;
        std::atomic_bool _isRunning;
        std::mutex _mtx;
    };
};