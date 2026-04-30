#include "services.hpp"
#include "errorservice.hpp"
#include "memoryservice.hpp"

using namespace ErrorService;
using namespace Services;

namespace MemoryService
{
    IMemoryService::String allocateString(const size_t size)
    {
        const auto result = memoryService().allocateString(size);
        rethrowHostError();
        return result;
    }

    IMemoryService::StringArray allocateStringArray(const size_t size)
    {
        const auto result = memoryService().allocateStringArray(size);
        rethrowHostError();
        return result;
    }

    IMemoryService::StringViewArray allocateStringViewArray(const size_t size)
    {
        const auto result = memoryService().allocateStringViewArray(size);
        rethrowHostError();
        return result;
    }

    IMemoryService::String copy(const std::string_view string)
    {
        const auto result = memoryService().copy(string.data());
        rethrowHostError();
        return result;
    }

    IMemoryService::StringView wrap(const std::string_view string)
    {
        const auto result = memoryService().wrap(string.data());
        rethrowHostError();
        return result;
    }

    void freeString(IMemoryService::String& data)
    {
        memoryService().freeString(&data);
        rethrowHostError();
    }

    void freeStringArray(IMemoryService::StringArray& data)
    {
        memoryService().freeStringArray(&data);
        rethrowHostError();
    }

    void freeStringViewArray(IMemoryService::StringViewArray& data)
    {
        memoryService().freeStringViewArray(&data);
        rethrowHostError();
    }

    // ====================================================================== //
    // String

    String::String(const size_t size) :
        string(allocateString(size)),
        std::string_view(string.data, string.size)
    {}

    String::String(const std::string_view string) :
        string(MemoryService::copy(string)),
        std::string_view(string.data(), string.size())
    {}

    String::String(const IMemoryService::String string) :
        string(string),
        std::string_view(string.data, string.size)
    {}

    String::~String()
    {
        freeString(string);
    }

    // ====================================================================== //
    // legacy

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
}
