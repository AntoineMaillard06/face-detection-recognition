#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sys/stat.h>

#include "./../Exception/Exception.hpp"

#define HEADER_REGEXP "^(P2|P5)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]"

namespace face {

    typedef struct pgm_header_s {
        bool is_binary;
        u_int32_t width;
        u_int32_t height;
        u_int16_t gray_scales;
    } pgm_header_t;

    class PGMReader {
        public:
        ~PGMReader();

        static long getFileSize(const std::string &fileName);
        void process(const std::string &path);

        const pgm_header_t &getHeader() const;

        private:
        void computeHeader();

        void freeContent();

        pgm_header_t _header;
        char *_content = nullptr;
    };
};
