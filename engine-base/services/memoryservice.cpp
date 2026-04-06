#include "services.hpp"
#include "memoryservice.hpp"

namespace MemoryService
{
    MemoryBlock::MemoryBlock(IMemoryService::MemoryBlock&& data) :
        data(data)
    {
        data.data = nullptr;
        data.size = 0;
    }

    MemoryBlock::MemoryBlock(const size_t size) :
        data(memoryService().allocate(size))
    {}

    MemoryBlock::MemoryBlock(std::string_view data) :
        data(memoryService().create(data.data(), data.size()))
    {}

    MemoryBlock::MemoryBlock(std::span<std::byte> data) :
        data(memoryService().create(
                 reinterpret_cast<char*>(data.data()),
                 data.size())
            )
    {}

    MemoryBlock::~MemoryBlock()
    {
        if (isValid())
        {
            memoryService().free(&data);
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
