#include <memory>

#include "./../Mat/Mat.hpp"

#define HEADER_REGEXP "^(P2|P5)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]([0-9]+)[\\t| |\\r?\\n]"
#define HEADER_ELEM_COUNT 4

namespace face {
    class PGMReader {
        public:
        ~PGMReader();

        static long getFileSize(const std::string &fileName);
        std::shared_ptr<face::Mat> process(const std::string &path);

        const pgm_header_t &getHeader() const;

        private:
        void computeHeader();
        std::shared_ptr<face::Mat> computeBinaryData(const u_char bytesPerPixel);
        std::shared_ptr<face::Mat> computeTextData();
        void skipHeader(uint32_t &index);

        void freeContent();

        pgm_header_t _header;
        char *_content = nullptr;
    };
};
