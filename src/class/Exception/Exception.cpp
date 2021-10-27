#include "./Exception.hpp"

face::Exception::Exception(const std::string &errMessage): _errMessage(errMessage)
{
}

const char* face::Exception::what() const noexcept
{
    return this->_errMessage.c_str();
}