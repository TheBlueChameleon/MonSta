#include "errorservice/catchmacros.hpp"

#include "handleconverter.hpp"
#include "jsonservice.hpp"
#include "jsonschemabuilder.hpp"
#include "jsonservice_schemabuilder_dlx.hpp"

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle HOST_API_CALL instantiateSchemaBuilder_dlx(const char* const name)
    {
        try
        {
            // *INDENT-OFF*
            if (name) {return toJsonSchemaBuilderHandle(*new JsonSchemaBuilder(name));}
            else      {return toJsonSchemaBuilderHandle(*new JsonSchemaBuilder(    ));}
            // *INDENT-ON*
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaBuilderHandle(nullptr))
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle instantiateSchemaElementBuilder_dlx(const char* const name)
    {
        try
        {
            return toJsonSchemaElementBuilderHandle(*new JsonSchemaElementBuilder(name));
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaElementBuilderHandle(nullptr))
    }

    void HOST_API_CALL freeSchemaBuilder_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle& handle)
    {
        try
        {
            assertSaneHandle(handle);
            delete &toSchemaBuilder(handle);
            handle.data = nullptr;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL freeSchemaElementBuilder_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle)
    {
        try
        {
            assertSaneHandle(handle);
            delete &toSchemaElementBuilder(handle);
            handle.data = nullptr;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void setAdditionalProperties(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const additionalProperties)
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(additionalProperties);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.setAdditionalProperties(parse(additionalProperties));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void addRequired(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const required)
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(required);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addRequired(required);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    IJsonServiceTypes::ModifiableJsonHandle addElement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const name)
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(name);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            auto& element = schema.addElement(name);
            return toModifiableJsonHandle(element);
        }
        CATCH_ABSTRACT_ERROR(nullptr)
        CATCH_JSON_ERROR(nullptr)
        CATCH_STD_EXCEPTION(nullptr)
    }

    void addReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName,
        const IJsonServiceTypes::JsonType type,
        bool setDefaults
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(propertyName);
            assertNonNullParseable(schemaName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addReference(propertyName, schemaName, type, setDefaults);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

}
