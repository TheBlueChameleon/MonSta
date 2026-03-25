#ifndef SYNCHRONIZEDOSTREAM_HPP
#define SYNCHRONIZEDOSTREAM_HPP

#include <concepts>
#include <memory>
#include <semaphore>

namespace FileService
{
    class StdOutPseudoFile;

    class SynchronizedOStream
    {
        private:
            std::binary_semaphore         smph;
            std::unique_ptr<std::ostream> stream;

        public:
            template <std::derived_from<std::ostream> T>
            SynchronizedOStream(std::unique_ptr<T>& stream) :
                smph(1),
                stream(stream.release())
            {}

            template <std::derived_from<std::ostream> T>
            SynchronizedOStream(std::unique_ptr<T>&& stream) :
                smph(1),
                stream(stream.release())
            {}


            SynchronizedOStream& write(const void* data, std::streamsize count);

            template <typename T>
            SynchronizedOStream& operator<<(const T& data)
            {
                smph.acquire();
                *stream << data;
                smph.release();

                return *this;
            }
    };
}

#endif // SYNCHRONIZEDOSTREAM_HPP
