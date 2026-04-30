#include "services/jsonservice/jsonservice_itemaccess.hpp"

#include "jsonwrapper.hpp"

namespace JsonService
{
    JsonWrapper::JsonWrapper(const IJsonServiceTypes::JsonHandle handle) : handle(handle)
    {}

    IJsonServiceTypes::JsonHandle JsonWrapper::getHandle() const
    {
        return handle;
    }

    JsonWrapper JsonWrapper::navigateTo(const std::string_view jsonPointer) const
    {
        return JsonService::navigateTo(handle, jsonPointer);
    }

    bool JsonWrapper::contains(const std::string_view elementName) const
    {
        return JsonService::contains(handle, elementName);
    }

    const IJsonServiceTypes::JsonType JsonWrapper::getType() const
    {
        return JsonService::getType(handle);
    }

    bool JsonWrapper::isNull() const
    {
        return JsonService::isNull(handle);
    }

    bool JsonWrapper::isBoolean() const
    {
        return JsonService::isBoolean(handle);
    }

    bool JsonWrapper::isInteger() const
    {
        return JsonService::isInteger(handle);
    }

    bool JsonWrapper::isUnsigned() const
    {
        return JsonService::isUnsigned(handle);
    }

    bool JsonWrapper::isFloat() const
    {
        return JsonService::isFloat(handle);
    }

    bool JsonWrapper::isString() const
    {
        return JsonService::isString(handle);
    }

    bool JsonWrapper::isArray() const
    {
        return JsonService::isArray(handle);
    }

    bool JsonWrapper::isObject() const
    {
        return JsonService::isObject(handle);
    }

    bool JsonWrapper::getAsBool() const
    {
        return JsonService::getAsBool(handle);
    }

    int JsonWrapper::getAsInteger() const
    {
        return JsonService::getAsInteger(handle);
    }

    unsigned long long JsonWrapper::getAsUnsigned() const
    {
        return JsonService::getAsUnsigned(handle);
    }

    double JsonWrapper::getAsFloat() const
    {
        return JsonService::getAsFloat(handle);
    }

    const std::string_view JsonWrapper::getAsString() const
    {
        return JsonService::getAsString(handle);
    }

    size_t JsonWrapper::getArraySize() const
    {
        return JsonService::getArraySize(handle);
    }

    JsonWrapper JsonWrapper::getArrayItem(const int index) const
    {
        return JsonService::getArrayItem(handle, index);
    }

    MemoryService::String JsonWrapper::dump(int indent) const
    {
        return JsonService::dump(handle, indent);
    }

} // namespace JsonService
