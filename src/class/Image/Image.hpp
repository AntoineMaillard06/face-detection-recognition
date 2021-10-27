#include <iostream>

#include "./../Exception/Exception.hpp"
#include "./../PGMReader/PGMReader.hpp"

namespace face {
    class Image {
        public:
        Image(const std::string &path);

        private:
        char *_content;
    };
};
