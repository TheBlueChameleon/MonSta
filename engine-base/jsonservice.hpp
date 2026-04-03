#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <IJsonService.hpp>

namespace JsonService
{
    const IJsonService::Handle get(const char* const tag);
    const IJsonService::Handle navigateTo(const IJsonService::Handle handle, const char* const jsonPointer);
    const bool contains(const IJsonService::Handle handle, const char* const elementName);
}

#endif // JSONSERVICE_HPP
