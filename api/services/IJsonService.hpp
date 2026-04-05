#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

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

        const EntryState(*getState)(const IJsonService::JsonTag tag);
        const JsonHandle(*get)(const IJsonService::JsonTag tag);
        const JsonHandle(*getOrAdd)(
            const IJsonService::JsonTag tag,
            const void(*creator)(const ModifiableJsonHandle)
        );
        const JsonHandle(*getOrParse)(
            const IJsonService::JsonTag tag,
            const char* const json
        );
        const ModifiableJsonHandle(*declare)(const IJsonService::JsonTag tag);
        const JsonHandle(*commit)(const IJsonService::JsonTag tag);

        const JsonHandle(*navigateTo)(const JsonHandle, const char* const jsonPointer);
        const bool (*containts)(const JsonHandle, const char* const elementName);

        const IJsonService::JsonType(*getType)(const IJsonService::JsonHandle handle);
        const bool (*isNull)(const IJsonService::JsonHandle handle);
        const bool (*isBoolean)(const IJsonService::JsonHandle handle);
        const bool (*isInteger)(const IJsonService::JsonHandle handle);
        const bool (*isUnsigned)(const IJsonService::JsonHandle handle);
        const bool (*isFloat)(const IJsonService::JsonHandle handle);
        const bool (*isString)(const IJsonService::JsonHandle handle);
        const bool (*isArray)(const IJsonService::JsonHandle handle);
        const bool (*isObject)(const IJsonService::JsonHandle handle);

        const bool (*getAsBool)(const IJsonService::JsonHandle handle);
        const int (*getAsInteger)(const IJsonService::JsonHandle handle);
        const unsigned long long (*getAsUnsigned)(const IJsonService::JsonHandle handle);
        const double (*getAsFloat)(const IJsonService::JsonHandle handle);
        const char* const(*getAsString)(const IJsonService::JsonHandle handle);

        const int (*getArraySize)(const IJsonService::JsonHandle handle);
        const IJsonService::JsonHandle(*getArrayItem)(const IJsonService::JsonHandle handle, const int index);

        void (*setToNull)(const IJsonService::ModifiableJsonHandle handle);
        void (*setToBool)(const IJsonService::ModifiableJsonHandle handle, const bool value);
        void (*setToInteger)(const IJsonService::ModifiableJsonHandle handle, const int value);
        void (*setToUnsigned)(const IJsonService::ModifiableJsonHandle handle, const unsigned value);
        void (*setToFloat)(const IJsonService::ModifiableJsonHandle handle, const double value);
        void (*setToString)(const IJsonService::ModifiableJsonHandle handle, const char* const value);
        void (*setToHandle)(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
        void (*setToArray)(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
        void (*setToObject)(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
        void (*setToParseable)(const IJsonService::ModifiableJsonHandle handle, const char* const source);

        const IJsonService::JsonHandle(*parseValidatePatchAndAdd)(
            const IJsonService::JsonTag     tag,
            const char* const               json,
            const IJsonService::JsonTag     validationSchemaTag
        );
        const IJsonService::JsonHandle(*readValidatePatchAndAdd)(
            const IJsonService::JsonTag tag,
            const char* const file,
            const IJsonService::JsonTag validationSchemaTag
        );
};

#endif // IJSONSERVICE_HPP
