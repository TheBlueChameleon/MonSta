#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

struct IJsonService
{
        enum class EntryState {NONEXISTENT, DECLARED, READY};

        struct JsonHandle
        {
            const void* data;
        };

        struct ModifiableJsonHandle :
            public JsonHandle
        {};

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
        const JsonHandle(*getOrAdd)(const IJsonService::JsonTag tag, const IJsonService::JsonHandle(*creator)());
        const ModifiableJsonHandle(*declare)(const IJsonService::JsonTag tag);
        const JsonHandle(*commit)(const IJsonService::JsonTag tag);

        const JsonHandle(*navigateTo)(const JsonHandle, const char* const jsonPointer);
        const bool (*containts)(const JsonHandle, const char* const elementName);

        const bool (*isString)(const JsonHandle);
        const char* const(*getAsString)(const JsonHandle);
};

#endif // IJSONSERVICE_HPP
