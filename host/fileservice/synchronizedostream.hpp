#ifndef SYNCHRONIZEDOSTREAM_HPP
#define SYNCHRONIZEDOSTREAM_HPP

#include <concepts>
#include <memory>
#include <mutex>

namespace FileService
{
    class StdOutStream;

    class SynchronizedOStream
    {
        private:
            std::mutex mutable            mutex;
            std::unique_ptr<std::ostream> stream;

        public:
            template <std::derived_from<std::ostream> T>
            SynchronizedOStream(std::unique_ptr<T>&& stream) :
                stream(stream.release())
            {}

            bool hasStream() const;
            void assertHasStream() const;

            SynchronizedOStream& write(const void* data, std::streamsize count);

            template <typename T>
            SynchronizedOStream& operator<<(const T& data)
            {
                auto lock = std::lock_guard(mutex);
                assertHasStream();
                *stream << data;

                return *this;
            }

            std::ostream* expose() const;
    };
}

#endif // SYNCHRONIZEDOSTREAM_HPP
