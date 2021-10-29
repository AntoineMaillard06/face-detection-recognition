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
        }
    }
}

void face::Window::windowJoin()
{
    this->_windowThread.join();
}
