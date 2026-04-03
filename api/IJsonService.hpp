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
};

#endif // IJSONSERVICE_HPP
