#include "errorservice/catchmacros.hpp"
#include "errorservice/errors.hpp"

#include "memoryservice.hpp"
#include "memoryservice_dlx.hpp"

namespace MemoryService
{
    static void assertSanePtr(const void* const data)
    {
        if (data == nullptr)
        {
            throw ClientRequestError("Client attempted memory operation on null ptr");
        }
    }

    static void assertSaneItemPtr(const void* const data, const int i)
    {
        if (data == nullptr)
        {
            throw ClientRequestError("Client attempted memory operation on null ptr in item #"s + std::to_string(i));
        }
    }

    IMemoryService::String HOST_API_CALL allocateString_dlx(const size_t size)
    {
        const auto nullstring = IMemoryService::String{nullptr, 0};
        try
        {
            return allocateString(size);
        }
        CATCH_ALL_OWN(nullstring)
    }

    IMemoryService::StringArray HOST_API_CALL allocateStringArray_dlx(const size_t size)
    {
        const auto nullArray = IMemoryService::StringArray{nullptr, 0};
        try
        {
            return allocateStringArray(size);
        }
        CATCH_ALL_OWN(nullArray)
    }

    IMemoryService::StringViewArray HOST_API_CALL allocateStringViewArray_dlx(const size_t size)
    {
        const auto nullArray = IMemoryService::StringViewArray{nullptr, 0};
        try
        {
            return allocateStringViewArray(size);
        }
        CATCH_ALL_OWN(nullArray)
    }

    IMemoryService::String HOST_API_CALL copy_dlx(const char* const string)
    {
        const auto nullstring = IMemoryService::String{nullptr, 0};
        try
        {
            assertSanePtr(string);
            return copy(std::string_view(string));
        }
        CATCH_ALL_OWN(nullstring)
    }

    IMemoryService::StringView HOST_API_CALL wrap_dlx(const char* const view)
    {
        const auto nullstring = IMemoryService::StringView{nullptr, 0};
        try
        {
            assertSanePtr(view);
            return wrap(std::string_view(view));
        }
        CATCH_ALL_OWN(nullstring)
    }

    void HOST_API_CALL freeString_dlx(IMemoryService::String* const data)
    {
        try
        {
            assertSanePtr(data);
            free(*data);
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL freeStringArray_dlx(IMemoryService::StringArray* const data)
    {
        try
        {
            assertSanePtr(data);
            for (int i = 0; i < data->size; ++i)
            {
                assertSaneItemPtr(data->data[i].data, i);
            }
            free(*data);
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL freeStringViewArray_dlx(IMemoryService::StringViewArray* const data)
    {
        try
        {
            assertSanePtr(data);
            for (int i = 0; i < data->size; ++i)
            {
                assertSaneItemPtr(data->data[i].data, i);
            }
            free(*data);
        }
        CATCH_ALL_OWN()
    }
}
