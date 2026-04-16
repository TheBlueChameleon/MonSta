#include "services.hpp"
#include "memoryservice.hpp"

namespace MemoryService
{
    IMemoryService::MemoryBlock allocate(const size_t size)
    {
        return memoryService().allocate(size);
    }

    IMemoryService::MemoryBlock create(const char* const data, size_t size)
    {
        return memoryService().create(data, size);
    }

    void free(IMemoryService::MemoryBlock* data)
    {
        return memoryService().free(data);
    }

    MemoryBlock::MemoryBlock(const size_t size) :
        data(allocate(size))
    {}

    MemoryBlock::MemoryBlock(std::string_view data) :
        data(create(data.data(), data.size()))
    {}

    MemoryBlock::MemoryBlock(std::span<std::byte> data) :
        data(create(
                 reinterpret_cast<char*>(data.data()),
                 data.size())
            )
    {}

    MemoryBlock::MemoryBlock(MemoryService::MemoryBlock&& other):
        data(other.data)
    {
        other.data.data = nullptr;
        other.data.size = 0;
    }

    MemoryBlock::MemoryBlock(IMemoryService::MemoryBlock&& data) :
        data(data)
    {
        data.data = nullptr;
        data.size = 0;
    }

    MemoryBlock::~MemoryBlock()
    {
        if (isValid())
        {
            free(&data);
        }
    }

    bool MemoryBlock::isValid() const
    {
        return data.data != nullptr;
    }

    int MemoryBlock::getSize() const
    {
        return data.size;
    }

    char* MemoryBlock::getRawBytes()
    {
        return data.data;
    }

    std::string_view MemoryBlock::getAsStringView()
    {
        return std::string_view(data.data, data.size);
    }

    std::span<std::byte> MemoryBlock::getAsBytes()
    {
        return std::span<std::byte>(
                   reinterpret_cast<std::byte*>(data.data),
                   data.size
               );
    }
}



