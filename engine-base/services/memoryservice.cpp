#include "base/errors.hpp"

#include "services.hpp"
#include "errorservice.hpp"
#include "memoryservice.hpp"

using namespace ErrorService;
using namespace Services;
using namespace std::string_literals;

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


    IMemoryService::StringArray copy(const std::span<std::string_view> array)
    {
        IMemoryService::StringArray result = allocateStringArray(array.size());
        for (int i = 0; i < array.size(); ++i)
        {
            result.data[i] = copy(array[i]);
        }
        return result;
    }

    IMemoryService::StringView wrap(const std::string_view string)
    {
        const auto result = memoryService().wrap(string.data());
        rethrowHostError();
        return result;
    }

    IMemoryService::StringViewArray wrap(const std::span<std::string_view> array)
    {
        const IMemoryService::StringViewArray result = memoryService().allocateStringViewArray(array.size());
        rethrowHostError();
        for (int i = 0; i < array.size(); ++i)
        {
            result.data[i] = wrap(array[i]);
        }
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
    // StringArray

    StringArray::StringArray(const size_t size) :
        m_array(allocateStringArray(size)),
        std::span<IMemoryService::String>(m_array.data, m_array.data + size)
    {}

    StringArray::StringArray(const std::span<std::string_view> array) :
        m_array(copy(array)),
        std::span<IMemoryService::String>(m_array.data, m_array.data + array.size())
    {}

    StringArray::StringArray(const IMemoryService::StringArray array) :
        m_array(array),
        std::span<IMemoryService::String>(m_array.data, m_array.data + array.size)
    {}

    StringArray::~StringArray()
    {
        freeStringArray(m_array);
    }

    const std::string_view StringArray::get(const size_t index)
    {
        if (index > m_array.size)
        {
            throw LookupError("Invalid index: "s + std::to_string(index));
        }

        const IMemoryService::String element = m_array.data[index];
        return std::string_view(element.data, element.size);
    }

    // ====================================================================== //
    // StringArray

    StringViewArray::StringViewArray(const size_t size) :
        m_array(allocateStringViewArray(size)),
        std::span<IMemoryService::StringView>(m_array.data, m_array.data + size)
    {}

    StringViewArray::StringViewArray(const std::span<std::string_view> array) :
        m_array(wrap(array)),
        std::span<IMemoryService::StringView>(m_array.data, m_array.data + array.size())
    {}

    StringViewArray::StringViewArray(const IMemoryService::StringViewArray array) :
        m_array(array),
        std::span<IMemoryService::StringView>(m_array.data, m_array.data + array.size)
    {}

    StringViewArray::~StringViewArray()
    {
        freeStringViewArray(m_array);
    }

    const std::string_view StringViewArray::get(const size_t index)
    {
        if (index > m_array.size)
        {
            throw LookupError("Invalid index: "s + std::to_string(index));
        }

        const IMemoryService::StringView element = m_array.data[index];
        return std::string_view(element.data, element.size);
    }

}


