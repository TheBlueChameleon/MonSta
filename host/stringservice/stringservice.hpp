#ifndef STRINGSERVICE_HPP
#define STRINGSERVICE_HPP

#include <string_view>

#include <IStringService.hpp>

namespace StringService
{
    IStringService exportService();

    IStringService::StringData allocate(const size_t size);

    IStringService::StringData createFromView(const std::string_view view);

    IStringService::StringData createFromCstr(const char* const data);

    void free(IStringService::StringData* stringData);
}

#endif // STRINGSERVICE_HPP
