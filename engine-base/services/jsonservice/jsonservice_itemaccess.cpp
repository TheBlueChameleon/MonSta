#include "services/services.hpp"

#include "jsonservice_itemaccess.hpp"

namespace JsonService
{
    const IJsonServiceTypes::JsonHandle navigateTo(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer)
    {
        const auto result = jsonService().itemAccess.navigateTo(handle, jsonPointer.data());
        rethrowHostError();
        return result;
    }

    IJsonServiceTypes::ModifiableJsonHandle navigateToModifiable(IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view jsonPointer)
    {
        const auto result = jsonService().itemAccess.navigateToModifiable(handle, jsonPointer.data());
        rethrowHostError();
        return result;
    }

    const bool contains(const IJsonServiceTypes::JsonHandle handle, const std::string_view elementName)
    {
        const auto result = jsonService().itemAccess.containts(handle, elementName.data());
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonType getType(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.getType(handle);
        rethrowHostError();
        return result;
    }

    const bool isNull(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isNull(handle);
        rethrowHostError();
        return result;
    }

    const bool isBoolean(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isBoolean(handle);
        rethrowHostError();
        return result;
    }

    const bool isInteger(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isInteger(handle);
        rethrowHostError();
        return result;
    }

    const bool isUnsigned(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isUnsigned(handle);
        rethrowHostError();
        return result;
    }

    const bool isFloat(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isFloat(handle);
        rethrowHostError();
        return result;
    }

    const bool isString(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isString(handle);
        rethrowHostError();
        return result;
    }

    const bool isObject(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isObject(handle);
        rethrowHostError();
        return result;
    }

    const bool isArray(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.isArray(handle);
        rethrowHostError();
        return result;
    }

    const bool getAsBool(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.getAsBool(handle);
        rethrowHostError();
        return result;
    }

    const int getAsInteger(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.getAsInteger(handle);
        rethrowHostError();
        return result;
    }

    const unsigned long long getAsUnsigned(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.getAsUnsigned(handle);
        rethrowHostError();
        return result;
    }

    const double getAsFloat(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.getAsFloat(handle);
        rethrowHostError();
        return result;
    }

    const std::string_view getAsString(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.getAsString(handle);
        rethrowHostError();
        return result;
    }

    const int getArraySize(const IJsonServiceTypes::JsonHandle handle)
    {
        const auto result = jsonService().itemAccess.getArraySize(handle);
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonHandle getArrayItem(const IJsonServiceTypes::JsonHandle handle, const int index)
    {
        const auto result = jsonService().itemAccess.getArrayItem(handle, index);
        rethrowHostError();
        return result;
    }

    void setToNull(const IJsonServiceTypes::ModifiableJsonHandle handle)
    {
        jsonService().itemAccess.setToNull(handle);
        rethrowHostError();
    }

    void setToBool(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value)
    {
        jsonService().itemAccess.setToBool(handle, value);
        rethrowHostError();
    }

    void setToInteger(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value)
    {
        jsonService().itemAccess.setToInteger(handle, value);
        rethrowHostError();
    }

    void setToUnsigned(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned int value)
    {
        jsonService().itemAccess.setToUnsigned(handle, value);
        rethrowHostError();
    }

    void setToFloat(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value)
    {
        jsonService().itemAccess.setToFloat(handle, value);
        rethrowHostError();
    }

    void setToString(const IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view value)
    {
        jsonService().itemAccess.setToString(handle, value.data());
        rethrowHostError();
    }

    void setToHandle(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        jsonService().itemAccess.setToHandle(handle, source);
        rethrowHostError();
    }

    void setToArray(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        jsonService().itemAccess.setToArray(handle, source);
        rethrowHostError();
    }

    void setToObject(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        jsonService().itemAccess.setToObject(handle, source);
        rethrowHostError();
    }

    void setToParseable(const IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view source)
    {
        jsonService().itemAccess.setToParseable(handle, source.data());
        rethrowHostError();
    }

    MemoryService::MemoryBlock dump(const IJsonServiceTypes::JsonHandle handle, int indent)
    {
        auto result = jsonService().itemAccess.dump(handle, indent);
        rethrowHostError();
        return result;
    }
}
