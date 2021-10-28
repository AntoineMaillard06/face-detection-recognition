#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <sys/stat.h>

#include "./../Exception/Exception.hpp"

namespace face {
    typedef struct pgm_header_s {
        bool is_binary;
        u_int32_t width;
        u_int32_t height;
        u_int32_t gray_scales;
    } pgm_header_t;

    class Mat {
        public:
        Mat(const pgm_header_t &header, const std::vector<u_int32_t> &data);

        const uint32_t getWidth() const;
        const uint32_t getHeight() const;
        const uint32_t getMaxGrayScale() const;

        private:
        const pgm_header_t _header;
        std::vector<u_int32_t> _data;
    };
};
