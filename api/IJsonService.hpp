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

        const EntryState(*getState)(const IJsonService::JsonTag tag);
        const JsonHandle(*get)(const IJsonService::JsonTag tag);
        const JsonHandle(*add)(const IJsonService::JsonTag tag, const JsonHandle handle);
        const JsonHandle(*getOrAdd)(
            const IJsonService::JsonTag tag,
            const void(*creator)(const ModifiableJsonHandle)
        );
        const ModifiableJsonHandle(*declare)(const IJsonService::JsonTag tag);
        const JsonHandle(*commit)(const IJsonService::JsonTag tag);

        const JsonHandle(*navigateTo)(const JsonHandle, const char* const jsonPointer);
        const bool (*containts)(const JsonHandle, const char* const elementName);

        const bool (*isString)(const JsonHandle);
        const char* const(*getAsString)(const JsonHandle);
};

#endif // IJSONSERVICE_HPP
