#include "./Window.hpp"

face::Window::Window():
    _windowThread(&face::Window::windowThread, this), _isRunning(true)
{
}

face::Window::~Window()
{
}

void face::Window::loadImage(const std::shared_ptr<face::Mat> &image)
{
    std::lock_guard<std::mutex> guard(this->_mtx);
    this->_image = image;
}

void face::Window::windowThread()
{
    this->_window.setFramerateLimit(50);

    while (this->_isRunning.load()) {
        std::lock_guard<std::mutex> guard(this->_mtx);

        if (this->_image != nullptr
        && !this->_window.isOpen()) {
            this->_window.create(
                sf::VideoMode(
                    this->_image->getWidth(),
                    this->_image->getHeight()
                ), "Image viewer"
            );
            this->_sfImage.create(
                this->_image->getWidth(),
                this->_image->getHeight(),
                this->_image->getPixels().get());
            this->_sfFaceTexture.loadFromImage(this->_sfImage);
            this->_sfSprite.setTexture(this->_sfFaceTexture);
        } else if (this->_image == nullptr
        && this->_window.isOpen()) {
            this->_window.close();
        }

        if (this->_window.isOpen()) {
            sf::Event event;
            while (this->_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    this->_window.close();
                    this->_isRunning.store(false);
                }
            }
            this->_window.clear(sf::Color::White);
            this->_window.draw(this->_sfSprite);
            this->_window.display();
        }
    }
}

void face::Window::windowJoin()
{
    this->_windowThread.join();
}
