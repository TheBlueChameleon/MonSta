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
    IMemoryService::StringView      wrap(const std::string_view string);

    void freeString(IMemoryService::String& data);
    void freeStringArray(IMemoryService::StringArray& data);
    void freeStringViewArray(IMemoryService::StringViewArray& data);

    class String : public std::string_view
    {
        private:
            IMemoryService::String string;

        public:
            String(const size_t size);
            String(const std::string_view string);
            String(const IMemoryService::String string);
            ~String();
    };

    // ====================================================================== //
    // legacy

    IMemoryService::MemoryBlock allocate(const size_t size);
    IMemoryService::MemoryBlock create(const char* const data, size_t size);
    void free(IMemoryService::MemoryBlock* data);
}

#endif // MEMORYSERVICE_HPP
