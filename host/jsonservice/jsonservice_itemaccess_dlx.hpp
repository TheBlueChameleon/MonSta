#ifndef JSONSERVICE_ITEMACCESS_DLX_HPP
#define JSONSERVICE_ITEMACCESS_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    const HOST_API_CALL IJsonServiceTypes::JsonHandle navigateTo_dlx(const IJsonServiceTypes::JsonHandle handle, const char* const jsonPointer);
    const bool HOST_API_CALL contains_dlx(const IJsonServiceTypes::JsonHandle handle, const char* const elementName);

    const IJsonServiceTypes::JsonType HOST_API_CALL getType_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isNull_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isBoolean_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isInteger_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isUnsigned_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isFloat_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isString_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isArray_dlx(const IJsonServiceTypes::JsonHandle handle);
    const bool HOST_API_CALL isObject_dlx(const IJsonServiceTypes::JsonHandle handle);

    const bool HOST_API_CALL getAsBool_dlx(const IJsonServiceTypes::JsonHandle handle);
    const int HOST_API_CALL getAsInteger_dlx(const IJsonServiceTypes::JsonHandle handle);
    const unsigned long long HOST_API_CALL getAsUnsigned_dlx(const IJsonServiceTypes::JsonHandle handle);
    const double HOST_API_CALL getAsFloat_dlx(const IJsonServiceTypes::JsonHandle handle);
    const char* const HOST_API_CALL getAsString_dlx(const IJsonServiceTypes::JsonHandle handle);

    const int HOST_API_CALL getArraySize_dlx(const IJsonServiceTypes::JsonHandle handle);
    const IJsonServiceTypes::JsonHandle HOST_API_CALL getArrayItem_dlx(const IJsonServiceTypes::JsonHandle handle, const int index);

    void HOST_API_CALL setToNull_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle);
    void HOST_API_CALL setToBool_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value);
    void HOST_API_CALL setToInteger_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value);
    void HOST_API_CALL setToUnsigned_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned value);
    void HOST_API_CALL setToFloat_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value);
    void HOST_API_CALL setToString_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const char* const value);
    void HOST_API_CALL setToHandle_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void HOST_API_CALL setToArray_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void HOST_API_CALL setToObject_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source);
    void HOST_API_CALL setToParseable_dlx(const IJsonServiceTypes::ModifiableJsonHandle handle, const char* const source);
}

#endif // JSONSERVICE_ITEMACCESS_DLX_HPP
