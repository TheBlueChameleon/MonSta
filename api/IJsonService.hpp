#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

struct IJsonService
{
    struct Handle
    {
        const void* data;
    };

    struct ModifiableHandle
    {
        const void* data;
    };

    const Handle(*get)(const char* const tag);
    const Handle(*navigateTo)(const Handle, const char* const jsonPointer);
    const bool (*containts)(const Handle, const char* const elementName);
};

#endif // IJSONSERVICE_HPP
