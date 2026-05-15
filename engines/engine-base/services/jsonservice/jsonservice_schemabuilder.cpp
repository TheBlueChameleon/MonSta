#include "services/errorservice.hpp"
#include "services/services.hpp"

#include "jsonservice_schemabuilder.hpp"

using namespace ErrorService;
using namespace Services;

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle instantiateSchemaBuilder(const std::string_view name)
    {
        auto result = jsonService().schemaBuilder.instantiateSchemaBuilder(name.data());
        rethrowHostError();
        return result;
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle instantiateSchemaElementBuilder(const std::string_view name)
    {
        auto result = jsonService().schemaBuilder.instantiateSchemaElementBuilder(name.data());
        rethrowHostError();
        return result;
    }

    void freeSchemaBuilder(IJsonServiceTypes::JsonSchemaBuilderHandle& handle)
    {
        jsonService().schemaBuilder.freeSchemaBuilder(&handle);
        rethrowHostError();
    }

    void freeSchemaElementBuilder(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle)
    {
        jsonService().schemaBuilder.freeSchemaElementBuilder(&handle);
        rethrowHostError();
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void sb_setAdditionalProperties(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view additionalProperties)
    {
        jsonService().schemaBuilder.sb_setAdditionalProperties(handle, additionalProperties.data());
        rethrowHostError();
    }

    void sb_addRequired(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view requiredPropertyName)
    {
        jsonService().schemaBuilder.sb_addRequired(handle, requiredPropertyName.data());
        rethrowHostError();
    }

    void sb_addAllOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.sb_addAllOfRequirement(handle, rawJson.data());
        rethrowHostError();
    }

    void sb_addAnyOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.sb_addAnyOfRequirement(handle, rawJson.data());
        rethrowHostError();
    }

    void sb_addOneOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.sb_addOneOfRequirement(handle, rawJson.data());
        rethrowHostError();
    }

    void sb_addNoneOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.sb_addNoneOfRequirement(handle, rawJson.data());
        rethrowHostError();
    }

    IJsonServiceTypes::ModifiableJsonHandle sb_addElementByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name
    )
    {
        auto result = jsonService().schemaBuilder.sb_addElementByName(handle, name.data());
        rethrowHostError();
        return result;
    }

    void sb_addElementByParseable(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name,
        const std::string_view rawJson
    )
    {
        jsonService().schemaBuilder.sb_addElementByParseable(handle, name.data(), rawJson.data());
        rethrowHostError();
    }

    void sb_addReferenceByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view schemaName,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        jsonService().schemaBuilder.sb_addReferenceByName(
            handle,
            propertyName.data(),
            schemaName.data(),
            propertyType,
            setDefaults
        );
        rethrowHostError();
    }

    void sb_addReferenceByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        jsonService().schemaBuilder.sb_addReferenceByType(
            handle,
            propertyName.data(),
            subSchema,
            propertyType,
            setDefaults
        );
        rethrowHostError();
    }

    IJsonServiceTypes::JsonSchemaBuilderHandle sb_addSubSchemaByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    )
    {
        auto result = jsonService().schemaBuilder.sb_addSubSchemaByName(handle, schemaName.data());
        rethrowHostError();
        return result;
    }

    void sb_addSubSchemaByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    )
    {
        jsonService().schemaBuilder.sb_addSubSchemaByType(handle, subSchema);
        rethrowHostError();
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName
    )
    {
        auto result = jsonService().schemaBuilder.sb_addPropertyByName(handle, propertyName.data());
        rethrowHostError();
        return result;
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByNameWithType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        IJsonServiceTypes::JsonType propertyType
    )
    {
        auto result = jsonService().schemaBuilder.sb_addPropertyByNameWithType(handle, propertyName.data(), propertyType);
        rethrowHostError();
        return result;
    }

    IJsonServiceTypes::JsonHandle sb_buildAndAdd(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    )
    {
        auto result = jsonService().schemaBuilder.sb_buildAndAdd(handle, tag);
        rethrowHostError();
        return result;
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder

    const std::string_view seb_getName(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        auto result = jsonService().schemaBuilder.seb_getName(handle);
        rethrowHostError();
        return result;
    }

    IJsonServiceTypes::ModifiableJsonHandle seb_getJson(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        auto result = jsonService().schemaBuilder.seb_getJson(handle);
        rethrowHostError();
        return result;
    }

    void seb_setJsonByHandle(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonHandle json)
    {
        jsonService().schemaBuilder.seb_setJsonByHandle(handle, json);
        rethrowHostError();
    }

    void seb_setJsonByParseable(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.seb_setJsonByParseable(handle, rawJson.data());
        rethrowHostError();
    }

    void seb_setProperty(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view rawJson
    )
    {
        jsonService().schemaBuilder.seb_setProperty(handle, propertyName.data(), rawJson.data());
        rethrowHostError();
    }

    void seb_setType(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        jsonService().schemaBuilder.seb_setType(handle, type);
        rethrowHostError();
    }

    void seb_setEnum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.seb_setEnum(handle, rawJson.data());
        rethrowHostError();
    }

    void seb_setTypedArray(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        jsonService().schemaBuilder.seb_setTypedArray(handle, type);
        rethrowHostError();
    }

    void seb_setEnumArray(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.seb_setEnumArray(handle, rawJson.data());
        rethrowHostError();
    }

    void seb_setDefault(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.seb_setDefault(handle, rawJson.data());
        rethrowHostError();
    }

    void seb_setMinimum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.seb_setMinimum(handle, rawJson.data());
        rethrowHostError();
    }

    void seb_setMaximum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        jsonService().schemaBuilder.seb_setMaximum(handle, rawJson.data());
        rethrowHostError();
    }

    void seb_setDescription(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view description)
    {
        jsonService().schemaBuilder.seb_setDescription(handle, description.data());
        rethrowHostError();
    }

    void seb_setTitle(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view title)
    {
        jsonService().schemaBuilder.seb_setDefault(handle, title.data());
        rethrowHostError();
    }

    void seb_setReference(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view subSchemaName)
    {
        jsonService().schemaBuilder.seb_setReference(handle, subSchemaName.data());
        rethrowHostError();
    }
}
