#include "synchronizedostream.hpp"

namespace FileService
{
    SynchronizedOStream& SynchronizedOStream::write(const void* data, std::streamsize count)
    {
        smph.acquire();
        stream->write(reinterpret_cast<const char*>(data), count);
        smph.release();

        return *this;
    }
}
