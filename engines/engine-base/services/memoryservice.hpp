#ifndef MEMORYSERVICE_HPP
#define MEMORYSERVICE_HPP

#include <span>
#include <string_view>

#include <services/IMemoryService.hpp>

namespace MemoryService
{
    IMemoryService::String          allocateString(const size_t size);
    IMemoryService::StringArray     allocateStringArray(const size_t size);
    IMemoryService::StringViewArray allocateStringViewArray(const size_t size);

    IMemoryService::String          copy(const std::string_view string);
    IMemoryService::StringArray     copy(const std::span<std::string_view> array);
    IMemoryService::StringView      wrap(const std::string_view string);
    IMemoryService::StringViewArray wrap(const std::span<std::string_view> array);

    void freeString(IMemoryService::String& data);
    void freeStringArray(IMemoryService::StringArray& data);
    void freeStringViewArray(IMemoryService::StringViewArray& data);

    class String : public std::string_view
    {
        private:
            IMemoryService::String m_string;

        public:
            String(const size_t size);
            String(const std::string_view string);
            String(const IMemoryService::String string);
            ~String();

            String(const String&) = delete;
            String& operator=(const String&) = delete;

            IMemoryService::String& getRaw();
    };

    class StringArray : public std::span<IMemoryService::String>
    {
        private:
            IMemoryService::StringArray m_array;

        public:
            StringArray(const size_t size);
            StringArray(const std::span<std::string_view> array);
            StringArray(const IMemoryService::StringArray array);
            ~StringArray();

            StringArray(const String&) = delete;
            StringArray& operator=(const StringArray&) = delete;

            const std::string_view get(const size_t index) const;
            IMemoryService::StringArray& getRaw();
    };

    class StringViewArray : public std::span<IMemoryService::StringView>
    {
        private:
            IMemoryService::StringViewArray m_array;

        public:
            StringViewArray(const size_t size);
            StringViewArray(const std::span<std::string_view> array);
            StringViewArray(const IMemoryService::StringViewArray array);
            ~StringViewArray();

            StringViewArray(const String&) = delete;
            StringViewArray& operator=(const StringViewArray&) = delete;

            const std::string_view get(const size_t index) const;
            IMemoryService::StringViewArray& getRaw();
    };
}

#endif // MEMORYSERVICE_HPP
