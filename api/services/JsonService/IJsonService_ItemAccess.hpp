#ifndef IJSONSERVICE_ITEMACCESS_HPP
#define IJSONSERVICE_ITEMACCESS_HPP

#include <CallingConventions.hpp>

#include <services/IMemoryService.hpp>

#include "IJsonService_Types.hpp"

struct IJsonService_ItemAccess
{
    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const navigateTo)(
        const IJsonServiceTypes::JsonHandle,
        const char* const jsonPointer
    );
    IJsonServiceTypes::ModifiableJsonHandle(HOST_API_CALL* const navigateToModifiable)(
        IJsonServiceTypes::ModifiableJsonHandle handle,
        const char* const jsonPointer
    );
    const bool (HOST_API_CALL* const containts)(const IJsonServiceTypes::JsonHandle, const char* const elementName);

    const IJsonServiceTypes::JsonType(HOST_API_CALL* const getType)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isNull)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isBoolean)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isInteger)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isUnsigned)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isFloat)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isString)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isArray)(const IJsonServiceTypes::JsonHandle handle);
    const bool (HOST_API_CALL* const isObject)(const IJsonServiceTypes::JsonHandle handle);

    const bool (HOST_API_CALL* const getAsBool)(const IJsonServiceTypes::JsonHandle handle);
    const int (HOST_API_CALL* const getAsInteger)(const IJsonServiceTypes::JsonHandle handle);
    const unsigned long long (HOST_API_CALL* const getAsUnsigned)(const IJsonServiceTypes::JsonHandle handle);
    const double (HOST_API_CALL* const getAsFloat)(const IJsonServiceTypes::JsonHandle handle);
    const char* const(HOST_API_CALL* const getAsString)(const IJsonServiceTypes::JsonHandle handle);

    const size_t (HOST_API_CALL* const getArraySize)(const IJsonServiceTypes::JsonHandle handle);
    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const getArrayItem)(const IJsonServiceTypes::JsonHandle handle, const int index);

    void (HOST_API_CALL* const setToNull)(const IJsonServiceTypes::ModifiableJsonHandle handle);
    void (HOST_API_CALL* const setToBool)(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value);
    void (HOST_API_CALL* const setToInteger)(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value);
    void (HOST_API_CALL* const setToUnsigned)(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned value);
    void (HOST_API_CALL* const setToFloat)(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value);
    void (HOST_API_CALL* const setToString)(const IJsonServiceTypes::ModifiableJsonHandle handle, const char* const value);
    void (HOST_API_CALL* const setToHandle)(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void (HOST_API_CALL* const setToArray)(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void (HOST_API_CALL* const setToObject)(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    IJsonServiceTypes::ModifiableJsonHandle(HOST_API_CALL* const setToParseable)(
        const IJsonServiceTypes::ModifiableJsonHandle handle,
        const char* const source
    );

    IMemoryService::String(HOST_API_CALL* const dump)(const IJsonServiceTypes::JsonHandle handle, int indent);
};

#endif // IJSONSERVICE_ITEMACCESS_HPP
