#include "errors.hpp"

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
            throw CriticalAbort("Attempting to write to invalid stream!");
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
