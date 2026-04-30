#include <cstring>

#include "memoryservice.hpp"
#include "memoryservice_dlx.hpp"

namespace MemoryService
{
    IMemoryService exportService()
    {
        return IMemoryService
        {
            allocateString_dlx,
            allocateStringArray_dlx,
            allocateStringViewArray_dlx,
            copy_dlx,
            wrap_dlx,
            freeString_dlx,
            freeStringArray_dlx,
            freeStringViewArray_dlx,

            allocate_dlx,
            create_dlx,
            freeString_dlx
        };
    }

    IMemoryService::String allocateString(const size_t size)
    {
        return IMemoryService::String{ new char[size], size };
    }

    IMemoryService::StringArray allocateStringArray(const size_t size)
    {
        return IMemoryService::StringArray{ new IMemoryService::String[size], size };
    }

    IMemoryService::StringViewArray allocateStringViewArray(const size_t size)
    {
        return IMemoryService::StringViewArray{ new IMemoryService::StringView[size], size };
    }

    IMemoryService::String copy(const std::string_view view)
    {
        IMemoryService::String result = allocateString(view.size() + 1);
        std::strncpy(result.data, view.data(), view.size());
        return result;
    }

    IMemoryService::StringArray copy(const std::span<std::string_view> view)
    {
        IMemoryService::StringArray result = allocateStringArray(view.size());
        int i = 0;
        for (const auto s : view)
        {
            result.data[i] = copy(s);
            ++i;
        }
        return result;
    }

    IMemoryService::StringArray copy(const std::span<std::string>& view)
    {
        IMemoryService::StringArray result = allocateStringArray(view.size());
        int i = 0;
        for (const auto s : view)
        {
            result.data[i] = copy(s);
            ++i;
        }
        return result;
    }

    IMemoryService::StringView wrap(const std::string_view view)
    {
        return IMemoryService::StringView{const_cast<char*>(view.data()), view.size() + 1};
    }

    IMemoryService::StringViewArray wrap(const std::span<std::string_view> view)
    {
        IMemoryService::StringViewArray result = allocateStringViewArray(view.size());
        for (int i = 0; i < view.size(); ++i)
        {
            result.data[i] = wrap(view[i]);
        }
        return result;
    }

    IMemoryService::StringViewArray wrap(const std::span<std::string>& view)
    {
        IMemoryService::StringViewArray result = allocateStringViewArray(view.size());
        for (int i = 0; i < view.size(); ++i)
        {
            result.data[i] = wrap(view[i]);
        }
        return result;
    }

    void free(IMemoryService::String& data)
    {
        delete data.data;
        data.data = nullptr;
        data.size = 0;
    }

    void free(IMemoryService::StringArray& data)
    {
        for (int i = 0; i < data.size; ++i)
        {
            free(data.data[i]);
        }

        delete data.data;
        data.data = nullptr;
        data.size = 0;
    }

    void free(IMemoryService::StringViewArray& data)
    {
        delete data.data;
        data.data = nullptr;
        data.size = 0;
    }

    // ====================================================================== //
    // legacy

    IMemoryService::MemoryBlock allocate(const size_t size)
    {
        return IMemoryService::MemoryBlock(
                   new char[size],
                   size
               );
    }


    IMemoryService::MemoryBlock createFromView(const std::string_view view)
    {
        const auto size = view.size() + 1;
        IMemoryService::MemoryBlock result = allocate(size);
        std::strncpy(result.data, view.data(), size);

        return result;
    }

    IMemoryService::MemoryBlock createFromView(const std::span<std::byte> view)
    {
        const auto size = view.size();
        IMemoryService::MemoryBlock result = allocate(size);
        std::memcpy(result.data, view.data(), size);

        return result;
    }

    void free(IMemoryService::MemoryBlock* data)
    {
        delete data->data;
        data->data = nullptr;
        data->size = 0;
    }

}
