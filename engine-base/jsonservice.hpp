#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <IJsonService.hpp>

namespace JsonService
{
    const IJsonService::JsonHandle get(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle navigateTo(const IJsonService::JsonHandle handle, const char* const jsonPointer);
    const bool contains(const IJsonService::JsonHandle handle, const char* const elementName);

    const bool isString(const IJsonService::JsonHandle handle);
    const char* const getAsString(const IJsonService::JsonHandle handle);
}

#endif // JSONSERVICE_HPP
