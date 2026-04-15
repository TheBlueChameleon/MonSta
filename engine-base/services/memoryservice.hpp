#ifndef MEMORYSERVICE_HPP
#define MEMORYSERVICE_HPP

#include <span>
#include <string_view>

#include <services/IMemoryService.hpp>

namespace MemoryService
{
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
