#ifndef IJSONSERVICE_ITEMACCESS_HPP
#define IJSONSERVICE_ITEMACCESS_HPP

#include <CallingConventions.hpp>

#include "IJsonService_Types.hpp"

struct IJsonService_ItemAccess
{
    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL navigateTo)(const IJsonServiceTypes::JsonHandle, const char* const jsonPointer);
    const bool (*const HOST_API_CALL containts)(const IJsonServiceTypes::JsonHandle, const char* const elementName);

    const IJsonServiceTypes::JsonType(*getType)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isNull)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isBoolean)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isInteger)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isUnsigned)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isFloat)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isString)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isArray)(const IJsonServiceTypes::JsonHandle handle);
    const bool (*const HOST_API_CALL isObject)(const IJsonServiceTypes::JsonHandle handle);

    const bool (*const HOST_API_CALL getAsBool)(const IJsonServiceTypes::JsonHandle handle);
    const int (*const HOST_API_CALL getAsInteger)(const IJsonServiceTypes::JsonHandle handle);
    const unsigned long long (*const HOST_API_CALL getAsUnsigned)(const IJsonServiceTypes::JsonHandle handle);
    const double (*const HOST_API_CALL getAsFloat)(const IJsonServiceTypes::JsonHandle handle);
    const char* const(*const HOST_API_CALL getAsString)(const IJsonServiceTypes::JsonHandle handle);

    const int (*const HOST_API_CALL getArraySize)(const IJsonServiceTypes::JsonHandle handle);
    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL getArrayItem)(const IJsonServiceTypes::JsonHandle handle, const int index);

    void (*const HOST_API_CALL setToNull)(const IJsonServiceTypes::ModifiableJsonHandle handle);
    void (*const HOST_API_CALL setToBool)(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value);
    void (*const HOST_API_CALL setToInteger)(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value);
    void (*const HOST_API_CALL setToUnsigned)(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned value);
    void (*const HOST_API_CALL setToFloat)(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value);
    void (*const HOST_API_CALL setToString)(const IJsonServiceTypes::ModifiableJsonHandle handle, const char* const value);
    void (*const HOST_API_CALL setToHandle)(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void (*const HOST_API_CALL setToArray)(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void (*const HOST_API_CALL setToObject)(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void (*const HOST_API_CALL setToParseable)(const IJsonServiceTypes::ModifiableJsonHandle handle, const char* const source);
};

#endif // IJSONSERVICE_ITEMACCESS_HPP
