#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <string_view>
#include <services/IJsonService.hpp>

namespace JsonService
{
    const IJsonServiceTypes::JsonHandle get(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle navigateTo(const IJsonServiceTypes::JsonHandle handle, const std::string_view jsonPointer);
    const bool contains(const IJsonServiceTypes::JsonHandle handle, const std::string_view elementName);

    const bool isString(const IJsonServiceTypes::JsonHandle handle);
    const std::string_view getAsString(const IJsonServiceTypes::JsonHandle handle);
}

#endif // JSONSERVICE_HPP
