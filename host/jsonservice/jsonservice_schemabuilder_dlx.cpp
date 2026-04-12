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

    void HOST_API_CALL sb_setAdditionalProperties_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const additionalProperties)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(additionalProperties);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.setAdditionalProperties(parse(additionalProperties));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL sb_addRequired_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const required)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(required);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addRequired(required);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL sb_addElementByName_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(name);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            auto& element = schema.addElement(name);
            return toModifiableJsonHandle(element);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
    }

    void HOST_API_CALL sb_addElementByParseable_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name,
        const char* const rawJson
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(name);
            assertSaneParseable(rawJson);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addElement(name, parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL sb_addReferenceByName_dlx(
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
            assertSaneParseable(propertyName);
            assertSaneParseable(schemaName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addReference(propertyName, schemaName, propertyType, setDefaults);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL sb_addReferenceByType_dlx(
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
            assertSaneParseable(propertyName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaBuilder& subSchema = toSchemaBuilder(subSchemaHandle);
            schema.addReference(propertyName, subSchema, propertyType, setDefaults);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    IJsonServiceTypes::JsonSchemaBuilderHandle HOST_API_CALL sb_addSubSchemaByName_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(schemaName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaBuilder& result = schema.addSubSchema(schemaName);
            return toJsonSchemaBuilderHandle(result);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaBuilderHandle{nullptr})
    }

    void HOST_API_CALL sb_addSubSchemaByType_dlx(
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
            schema.addSubSchema(subSchema);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL sb_addPropertyByName_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(propertyName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaElementBuilder& result = schema.addProperty(propertyName);
            return toJsonSchemaElementBuilderHandle(result);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL sb_addPropertyByNameWithType_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        IJsonServiceTypes::JsonType propertyType
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(propertyName);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            JsonSchemaElementBuilder& result = schema.addProperty(propertyName, propertyType);
            return toJsonSchemaElementBuilderHandle(result);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaElementBuilderHandle{nullptr})
    }

    IJsonServiceTypes::JsonHandle HOST_API_CALL sb_buildAndAdd_dlx(
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

    void HOST_API_CALL sb_addAllOfRequirement_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addAllOfRequirements(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL sb_addAnyOfRequirement_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addAnyOfRequirements(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL sb_addOneOfRequirement_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addOneOfRequirements(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL sb_addNoneOfRequirement_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaBuilder& schema = toSchemaBuilder(handle);
            schema.addNoneOfRequirements(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder

    const char* const HOST_API_CALL seb_getName_dlx(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            return element.getName().data();
        }
        CATCH_ABSTRACT_ERROR(nullptr)
        CATCH_JSON_ERROR(nullptr)
        CATCH_STD_EXCEPTION(nullptr)
    }

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL seb_getJson_dlx(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            nlohmann::ordered_json& result = element.getJson();
            return toModifiableJsonHandle(result);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
        CATCH_JSON_ERROR(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
        CATCH_STD_EXCEPTION(IJsonServiceTypes::ModifiableJsonHandle{nullptr})
    }

    void HOST_API_CALL seb_setJsonByHandle_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonHandle json
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneHandle(json);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setJson(toOrderedJson(json));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setJsonByParseable_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setJson(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setProperty_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const propertyName,
        const char* const rawJson
    )
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(propertyName);
            assertSaneParseable(rawJson);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setProperty(propertyName, parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setType_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        try
        {
            assertSaneHandle(handle);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setType(type);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setEnum_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setEnum(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setTypedArray_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        try
        {
            assertSaneHandle(handle);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setTypedArray(type);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setEnumArray_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setEnumArray(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setDefault_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setDefault(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setMinimum_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setMinimum(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setMaximum_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const rawJson)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(rawJson);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setMaximum(parse(rawJson));
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setDescription_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const description)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(description);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setDescription(description);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setTitle_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const title)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(title);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setTitle(title);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL seb_setReference_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const char* const subSchemaName)
    {
        try
        {
            assertSaneHandle(handle);
            assertSaneParseable(subSchemaName);
            JsonSchemaElementBuilder& element = toSchemaElementBuilder(handle);
            element.setReference(subSchemaName);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }
}
