#include "services.hpp"
#include "errorservice.hpp"
#include "memoryservice.hpp"

using namespace ErrorService;
using namespace Services;

namespace MemoryService
{
    IMemoryService::MemoryBlock allocate(const size_t size)
    {
        const auto result = memoryService().allocate(size);
        rethrowHostError();
        return result;
    }

    IMemoryService::MemoryBlock create(const char* const data, size_t size)
    {
        const auto result = memoryService().create(data, size);
        rethrowHostError();
        return result;
    }

    void free(IMemoryService::MemoryBlock* data)
    {
        memoryService().free(data);
        rethrowHostError();
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



