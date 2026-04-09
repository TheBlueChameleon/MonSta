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

    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL instantiateSchemaElementBuilder_dlx(const char* const name)
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

    void HOST_API_CALL setAdditionalProperties(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const additionalProperties)
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

    void HOST_API_CALL addRequired(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const required)
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

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL addElement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const name)
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(name);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            auto& element = schema.addElement(name);
            return toModifiableJsonHandle(element);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
    }

    void HOST_API_CALL addReferenceByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(propertyName);
            assertNonNullParseable(schemaName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addReference(propertyName, schemaName, propertyType, setDefaults);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL addReferenceByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchemaHandle,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneHandle(subSchemaHandle);
            assertNonNullParseable(propertyName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaBuilder& subSchema = toSchemaBuilder(subSchemaHandle);
            schema.addReference(propertyName, subSchema, propertyType, setDefaults);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    IJsonServiceTypes::JsonSchemaBuilderHandle HOST_API_CALL addSubSchemaByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(schemaName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaBuilder& result = schema.addSubSchema(schemaName);
            return toJsonSchemaBuilderHandle(result);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaBuilderHandle{nullptr})
    }

    void HOST_API_CALL addSubSchemaByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchemaHandle
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneHandle(subSchemaHandle);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaBuilder& subSchema = toSchemaBuilder(subSchemaHandle);
            JsonSchemaBuilder& result = schema.addSubSchema(subSchema);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL addPropertyByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(propertyName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaElementBuilder& result = schema.addProperty(propertyName);
            return toJsonSchemaElementBuilderHandle(result);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL addPropertyByNameWithType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        IJsonServiceTypes::JsonType propertyType
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertNonNullParseable(propertyName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaElementBuilder& result = schema.addProperty(propertyName, propertyType);
            return toJsonSchemaElementBuilderHandle(result);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
    }

    IJsonServiceTypes::JsonHandle HOST_API_CALL buildAndAdd(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneTag(tag);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            nlohmann::ordered_json result = schema.build();
            const nlohmann::ordered_json& ref = getOrAdd(tag, std::move(result));
            return toJsonHandle(ref);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle{nullptr})
    }

}
