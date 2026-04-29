#ifndef STDOUTSTREAM_HPP
#define STDOUTSTREAM_HPP

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

#endif // STDOUTSTREAM_HPP
