#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

#include <CallingConventions.hpp>

struct IJsonService
{
        enum class EntryState {NONEXISTENT, DECLARED, READY, ERROR};
        enum class JsonType {VOID, OBJECT, ARRAY, STRING, BOOLEAN, INTEGER, UNSIGNED, FLOAT, BINARY, DISCARDED};

        struct JsonHandle
        {
            const void* data;
        };

        struct ModifiableJsonHandle :
            public JsonHandle
        {
            ModifiableJsonHandle(const void* const data):
                JsonHandle(data)
            {}
        };

        struct JsonTag
        {
            const char* const name;

            JsonTag(const char* const name) :
                name(name)
            {}
        };

        struct JsonElementBuilderHandle
        {
            const void* data;
        };

        struct JsonSubSchemaBuilderHandle
        {
            const void* data;
        };

        struct JsonSchemaBuilderHandle
        {
            const void* data;
        };

        const EntryState(*const HOST_API_CALL getState)(const IJsonService::JsonTag tag);
        const JsonHandle(*const HOST_API_CALL get)(const IJsonService::JsonTag tag);
        const JsonHandle(*const HOST_API_CALL getOrAdd)(
            const IJsonService::JsonTag tag,
            const void(*const HOST_API_CALL creator)(const ModifiableJsonHandle)
        );
        const JsonHandle(*const HOST_API_CALL getOrParse)(
            const IJsonService::JsonTag tag,
            const char* const json
        );
        const ModifiableJsonHandle(*const HOST_API_CALL declare)(const IJsonService::JsonTag tag);
        const JsonHandle(*const HOST_API_CALL commit)(const IJsonService::JsonTag tag);

        const JsonHandle(*const HOST_API_CALL navigateTo)(const JsonHandle, const char* const jsonPointer);
        const bool (*const HOST_API_CALL containts)(const JsonHandle, const char* const elementName);

        const IJsonService::JsonType(*getType)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isNull)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isBoolean)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isInteger)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isUnsigned)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isFloat)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isString)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isArray)(const IJsonService::JsonHandle handle);
        const bool (*const HOST_API_CALL isObject)(const IJsonService::JsonHandle handle);

        const bool (*const HOST_API_CALL getAsBool)(const IJsonService::JsonHandle handle);
        const int (*const HOST_API_CALL getAsInteger)(const IJsonService::JsonHandle handle);
        const unsigned long long (*const HOST_API_CALL getAsUnsigned)(const IJsonService::JsonHandle handle);
        const double (*const HOST_API_CALL getAsFloat)(const IJsonService::JsonHandle handle);
        const char* const(*const HOST_API_CALL getAsString)(const IJsonService::JsonHandle handle);

        const int (*const HOST_API_CALL getArraySize)(const IJsonService::JsonHandle handle);
        const IJsonService::JsonHandle(*const HOST_API_CALL getArrayItem)(const IJsonService::JsonHandle handle, const int index);

        void (*const HOST_API_CALL setToNull)(const IJsonService::ModifiableJsonHandle handle);
        void (*const HOST_API_CALL setToBool)(const IJsonService::ModifiableJsonHandle handle, const bool value);
        void (*const HOST_API_CALL setToInteger)(const IJsonService::ModifiableJsonHandle handle, const int value);
        void (*const HOST_API_CALL setToUnsigned)(const IJsonService::ModifiableJsonHandle handle, const unsigned value);
        void (*const HOST_API_CALL setToFloat)(const IJsonService::ModifiableJsonHandle handle, const double value);
        void (*const HOST_API_CALL setToString)(const IJsonService::ModifiableJsonHandle handle, const char* const value);
        void (*const HOST_API_CALL setToHandle)(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
        void (*const HOST_API_CALL setToArray)(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
        void (*const HOST_API_CALL setToObject)(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
        void (*const HOST_API_CALL setToParseable)(const IJsonService::ModifiableJsonHandle handle, const char* const source);

        const IJsonService::JsonHandle(*const HOST_API_CALL parseValidatePatchAndAdd)(
            const IJsonService::JsonTag     tag,
            const char* const               json,
            const IJsonService::JsonTag     validationSchemaTag
        );
        const IJsonService::JsonHandle(*const HOST_API_CALL readValidatePatchAndAdd)(
            const IJsonService::JsonTag tag,
            const char* const file,
            const IJsonService::JsonTag validationSchemaTag
        );
};

#endif // IJSONSERVICE_HPP
