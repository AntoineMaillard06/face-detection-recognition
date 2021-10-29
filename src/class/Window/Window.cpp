#include "./Window.hpp"

face::Window::~Window()
{
}

void face::Window::addImage(const face::Mat &image)
{
    this->images.push_back(image);
}
