#ifndef JSONSERVICE_ITEMACCESS_HPP
#define JSONSERVICE_ITEMACCESS_HPP

#include <filesystem>
#include <string_view>

#include <services/IJsonService.hpp>

#include "services/memoryservice.hpp"

namespace JsonService
{
    const IJsonServiceTypes::JsonHandle navigateTo(const IJsonServiceTypes::JsonHandle handle, const std::string_view jsonPointer);
    IJsonServiceTypes::ModifiableJsonHandle navigateToModifiable(IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view jsonPointer);
    const bool contains(const IJsonServiceTypes::JsonHandle handle, const std::string_view elementName);

    const IJsonServiceTypes::JsonType getType(const IJsonServiceTypes::JsonHandle handle);
    const bool isNull(const IJsonServiceTypes::JsonHandle handle);
    const bool isBoolean(const IJsonServiceTypes::JsonHandle handle);
    const bool isInteger(const IJsonServiceTypes::JsonHandle handle);
    const bool isUnsigned(const IJsonServiceTypes::JsonHandle handle);
    const bool isFloat(const IJsonServiceTypes::JsonHandle handle);
    const bool isString(const IJsonServiceTypes::JsonHandle handle);
    const bool isArray(const IJsonServiceTypes::JsonHandle handle);
    const bool isObject(const IJsonServiceTypes::JsonHandle handle);

    const bool               getAsBool(const IJsonServiceTypes::JsonHandle handle);
    const int                getAsInteger(const IJsonServiceTypes::JsonHandle handle);
    const unsigned long long getAsUnsigned(const IJsonServiceTypes::JsonHandle handle);
    const double             getAsFloat(const IJsonServiceTypes::JsonHandle handle);
    const std::string_view   getAsString(const IJsonServiceTypes::JsonHandle handle);

    const size_t getArraySize(const IJsonServiceTypes::JsonHandle handle);
    const IJsonServiceTypes::JsonHandle getArrayItem(const IJsonServiceTypes::JsonHandle handle, const int index);

    void setToNull(const IJsonServiceTypes::ModifiableJsonHandle handle);
    void setToBool(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value);
    void setToInteger(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value);
    void setToUnsigned(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned value);
    void setToFloat(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value);
    void setToString(const IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view value);
    void setToHandle(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void setToArray(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void setToObject(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    IJsonServiceTypes::ModifiableJsonHandle setToParseable(
        const IJsonServiceTypes::ModifiableJsonHandle handle,
        const std::string_view source
    );

    MemoryService::MemoryBlock dump(const IJsonServiceTypes::JsonHandle handle, int indent = 2);
}

#endif // JSONSERVICE_ITEMACCESS_HPP
