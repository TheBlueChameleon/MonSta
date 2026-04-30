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
            IMemoryService::String data;

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

    class MemoryBlock
    {
        private:
            IMemoryService::MemoryBlock data;

        public:
            MemoryBlock(const size_t size);
            MemoryBlock(std::string_view data);
            MemoryBlock(std::span<std::byte> data);

            MemoryBlock(MemoryService::MemoryBlock&& other);
            MemoryBlock(IMemoryService::MemoryBlock&& data);
            ~MemoryBlock();

            MemoryBlock() = delete;
            MemoryBlock(const IMemoryService::MemoryBlock& data) = delete;
            MemoryBlock(const MemoryBlock&) = delete;

            MemoryBlock& operator=(const MemoryBlock&) = delete;
            MemoryBlock& operator=(MemoryBlock&&) = delete;

            bool isValid() const;
            int getSize() const;
            char* getRawBytes();
            std::string_view getAsStringView();
            std::span<std::byte> getAsBytes();
    };
}

#endif // MEMORYSERVICE_HPP
