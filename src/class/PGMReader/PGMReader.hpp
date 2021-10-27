#include <string>
#include <sys/stat.h>

namespace face {
    class PGMReader {
        public:
        static long getFileSize(const std::string &fileName);
    };
};
