#include <format>

#include "errorservice/errors.hpp"

#include "synchronizedostream.hpp"

namespace FileService
{
    bool SynchronizedOStream::hasStream() const
    {
        return static_cast<bool>(stream);
    }

    void SynchronizedOStream::assertHasStream() const
    {
        if (!hasStream())
        {
            throw IOError(std::format("Attempting to write to invalid stream for file '{}'!", path.c_str()));
        }
    }

    SynchronizedOStream& SynchronizedOStream::write(const void* data, std::streamsize count)
    {
        auto lock = std::lock_guard(mutex);
        assertHasStream();
        stream->write(reinterpret_cast<const char*>(data), count);

        return *this;
    }

    std::ostream* SynchronizedOStream::expose() const
    {
        return stream.get();
    }
}
