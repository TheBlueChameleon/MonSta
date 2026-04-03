#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

struct IJsonService
{
        enum class EntryState {NONEXISTENT, DECLARED, READY};

        struct Handle
        {
            const void* data;
        };

        struct ModifiableHandle :
            public Handle
        {};

        const EntryState(*getState)(const char* const tag);
        const Handle(*get)(const char* const tag);
        const Handle(*add)(const char* const tag, const Handle handle);
        const Handle(*getOrAdd)(const char* const tag, const IJsonService::Handle(*creator)());
        const ModifiableHandle(*declare)(const char* const tag);
        const Handle(*commit)(const char* const tag);

        const Handle(*navigateTo)(const Handle, const char* const jsonPointer);
        const bool (*containts)(const Handle, const char* const elementName);

        const bool (*isString)(const Handle);
        const char* const(*getAsString)(const Handle);
};

#endif // IJSONSERVICE_HPP
