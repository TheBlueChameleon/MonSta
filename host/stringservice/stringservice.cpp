#include <cstring>

#include "stringservice.hpp"

namespace StringService
{
    IStringService exportService()
    {
        return IStringService
        {
            allocate,
            createFromCstr,
            free
        };
    }

    IStringService::StringData allocate(const size_t size)
    {
        return IStringService::StringData(
                   new char[size],
                   size
               );
    }


    IStringService::StringData createFromView(const std::string_view view)
    {
        const auto size = view.size();
        IStringService::StringData result = allocate(size);
        std::strncpy(result.data, view.data(), size);

        return result;
    }

    IStringService::StringData createFromCstr(const char* const data)
    {
        const auto size = std::strlen(data);
        IStringService::StringData result = allocate(size);
        std::strncpy(result.data, data, size);

        return result;
    }

    void free(IStringService::StringData* stringData)
    {
        delete stringData->data;
        stringData->data = nullptr;
        stringData->size = 0;
    }

}
