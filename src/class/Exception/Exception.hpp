#include <exception>
#include <string>

namespace face {
    class Exception: public std::exception {
        public:
        Exception(const std::string &errMessage);
        virtual const char* what() const noexcept;

        private:
        const std::string _errMessage;
    };
};