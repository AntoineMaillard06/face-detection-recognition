#include "./Mat.hpp"

face::Mat::Mat(const face::pgm_header_t &header, const std::vector<u_int32_t> &data):
_header(header), _data(data)
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
