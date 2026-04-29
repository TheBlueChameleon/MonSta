#ifndef IJSONSERVICE_TYPES_HPP
#define IJSONSERVICE_TYPES_HPP

namespace IJsonServiceTypes
{
    enum class EntryState {NONEXISTENT, DECLARED, READY, ERROR};
    enum class JsonType {VOID, OBJECT, ARRAY, STRING, BOOLEAN, INTEGER, UNSIGNED, FLOAT, BINARY, DISCARDED};

    struct JsonTag
    {
        const char* const name;

        explicit JsonTag(const char* const name) :
            name(name)
        {}
    };

    struct ModifiableJsonHandle
    {
        const void* data;
    };

    struct JsonHandle
    {
        const void* data;

        JsonHandle(const void* data) :
            data(data)
        {}

        JsonHandle(const ModifiableJsonHandle other) :
            data(other.data)
        {}
    };

    struct JsonSchemaBuilderHandle
    {
        void* data;
    };

    struct JsonSchemaElementBuilderHandle
    {
        void* data;
    };
}

#endif // IJSONSERVICE_TYPES_HPP
