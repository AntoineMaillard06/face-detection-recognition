#include "./Mat.hpp"

face::Mat::Mat(const face::pgm_header_t &header, const std::shared_ptr<uint8_t[]> &data):
_header(header), _pixels(data)
{

}

const uint32_t face::Mat::getWidth() const
{
    return this->_header.width;
}

const uint32_t face::Mat::getHeight() const
{
    return this->_header.height;
}

const uint32_t face::Mat::getMaxGrayScale() const
{
    return this->_header.gray_scales;
}

const std::shared_ptr<uint8_t[]> &face::Mat::getPixels() const
{
    return this->_pixels;
}
