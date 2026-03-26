#ifndef NULLSTREAM_HPP
#define NULLSTREAM_HPP

#include <ostream>

namespace FileService
{
    class NullStream : public std::ostream
    {
        public:
            NullStream() = default;
            ~NullStream() = default;
    };
}

#endif // NULLSTREAM_HPP
