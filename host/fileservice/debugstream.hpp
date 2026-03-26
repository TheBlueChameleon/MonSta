#ifndef DEBUGSTREAM_HPP
#define DEBUGSTREAM_HPP

#include <sstream>

namespace FileService
{
    class DebugStream : public std::ostringstream
    {
        public:
            DebugStream() = default;
            ~DebugStream() = default;
    };
}

#endif // DEBUGSTREAM_HPP
