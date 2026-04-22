#ifndef JSONWRAPPER_HPP
#define JSONWRAPPER_HPP

#include <string_view>

#include <services/JsonService/IJsonService_Types.hpp>

#include "services/memoryservice.hpp"

namespace JsonService
{
    class JsonWrapper
    {
        private:
            const IJsonServiceTypes::JsonHandle handle;

        public:
            JsonWrapper(const IJsonServiceTypes::JsonHandle handle);

            IJsonServiceTypes::JsonHandle getHandle() const;

            JsonWrapper navigateTo(const std::string_view jsonPointer) const;
            bool contains(const std::string_view elementName) const;

            const IJsonServiceTypes::JsonType getType() const;
            bool isNull() const;
            bool isBoolean() const;
            bool isInteger() const;
            bool isUnsigned() const;
            bool isFloat() const;
            bool isString() const;
            bool isArray() const;
            bool isObject() const;

            bool                   getAsBool() const;
            int                    getAsInteger() const;
            unsigned long long     getAsUnsigned() const;
            double                 getAsFloat() const;
            const std::string_view getAsString() const;

            int getArraySize(const IJsonServiceTypes::JsonHandle handle) const;
            JsonWrapper getArrayItem(const IJsonServiceTypes::JsonHandle handle, const int index) const;

            MemoryService::MemoryBlock dump(int indent = 2) const;
    };

} // namespace JsonService

#endif // JSONWRAPPER_HPP
