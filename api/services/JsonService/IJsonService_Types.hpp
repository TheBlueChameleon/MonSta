#ifndef IJSONSERVICE_TYPES_H
#define IJSONSERVICE_TYPES_H

namespace IJsonServiceTypes
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
}

#endif // IJSONSERVICE_TYPES_H
