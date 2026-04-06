#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <string_view>
#include <services/IJsonService.hpp>

namespace JsonService
{
    const IJsonService::JsonHandle get(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle navigateTo(const IJsonService::JsonHandle handle, const std::string_view jsonPointer);
    const bool contains(const IJsonService::JsonHandle handle, const std::string_view elementName);

    const bool isString(const IJsonService::JsonHandle handle);
    const std::string_view getAsString(const IJsonService::JsonHandle handle);
}

#endif // JSONSERVICE_HPP
