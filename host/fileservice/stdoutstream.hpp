#ifndef STDOUTSTREAM_H
#define STDOUTSTREAM_H

#include <sstream>

namespace FileService
{
    class StdOutStream : public std::ostringstream
    {
        private:
            std::string title;

        public:
            StdOutStream(const std::string& title);
            ~StdOutStream();

            std::ostream& flush();
    };
}

#endif // STDOUTSTREAM_H
