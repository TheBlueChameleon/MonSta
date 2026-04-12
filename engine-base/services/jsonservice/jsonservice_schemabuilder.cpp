#include "services/services.hpp"

#include "jsonservice_schemabuilder.hpp"

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle instantiateSchemaBuilder(const std::string_view name)
    {
        return jsonService().schemaBuilder.instantiateSchemaBuilder(name.data());
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle instantiateSchemaElementBuilder(const std::string_view name)
    {
        return jsonService().schemaBuilder.instantiateSchemaElementBuilder(name.data());
    }
    void freeSchemaBuilder(IJsonServiceTypes::JsonSchemaBuilderHandle& handle)
    {
        return jsonService().schemaBuilder.freeSchemaBuilder(handle);
    }

    void freeSchemaElementBuilder(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle)
    {
        return jsonService().schemaBuilder.freeSchemaElementBuilder(handle);
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void sb_setAdditionalProperties(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view additionalProperties)
    {
        return jsonService().schemaBuilder.sb_setAdditionalProperties(handle, additionalProperties.data());
    }

    void sb_addRequired(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view requiredPropertyName)
    {
        return jsonService().schemaBuilder.sb_addRequired(handle, requiredPropertyName.data());
    }

    void sb_addAllOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.sb_addAllOfRequirement(handle, rawJson.data());
    }

    void sb_addAnyOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.sb_addAnyOfRequirement(handle, rawJson.data());
    }

    void sb_addOneOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.sb_addOneOfRequirement(handle, rawJson.data());
    }

    void sb_addNoneOfRequirement(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.sb_addNoneOfRequirement(handle, rawJson.data());
    }

    IJsonServiceTypes::ModifiableJsonHandle sb_addElementByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name
    )
    {
        return jsonService().schemaBuilder.sb_addElementByName(handle, name.data());
    }

    void sb_addElementByParseable(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name,
        const std::string_view rawJson
    )
    {
        return jsonService().schemaBuilder.sb_addElementByParseable(handle, name.data(), rawJson.data());
    }

    void sb_addReferenceByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view schemaName,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        return jsonService().schemaBuilder.sb_addReferenceByName(
                   handle,
                   propertyName.data(),
                   schemaName.data(),
                   propertyType,
                   setDefaults
               );
    }

    void sb_addReferenceByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        return jsonService().schemaBuilder.sb_addReferenceByType(
                   handle,
                   propertyName.data(),
                   subSchema,
                   propertyType,
                   setDefaults
               );
    }

    IJsonServiceTypes::JsonSchemaBuilderHandle sb_addSubSchemaByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    )
    {
        return jsonService().schemaBuilder.sb_addSubSchemaByName(handle, schemaName.data());
    }

    void sb_addSubSchemaByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    )
    {
        return jsonService().schemaBuilder.sb_addSubSchemaByType(handle, subSchema);
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName
    )
    {
        return jsonService().schemaBuilder.sb_addPropertyByName(handle, propertyName.data());
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByNameWithType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        IJsonServiceTypes::JsonType propertyType
    )
    {
        return jsonService().schemaBuilder.sb_addPropertyByNameWithType(handle, propertyName.data(), propertyType);
    }

    IJsonServiceTypes::JsonHandle sb_buildAndAdd(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    )
    {
        return jsonService().schemaBuilder.sb_buildAndAdd(handle, tag);
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder

    const std::string_view seb_getName(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        return jsonService().schemaBuilder.seb_getName(handle);
    }

    IJsonServiceTypes::ModifiableJsonHandle seb_getJson(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        return jsonService().schemaBuilder.seb_getJson(handle);
    }

    void seb_setJsonByHandle(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonHandle json)
    {
        return jsonService().schemaBuilder.seb_setJsonByHandle(handle, json);
    }

    void seb_setJsonByParseable(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setJsonByParseable(handle, rawJson.data());
    }

    void seb_setProperty(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view rawJson
    )
    {
        return jsonService().schemaBuilder.seb_setProperty(handle, propertyName.data(), rawJson.data());
    }

    void seb_setType(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        return jsonService().schemaBuilder.seb_setType(handle, type);
    }

    void seb_setEnum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setEnum(handle, rawJson.data());
    }

    void seb_setTypedArray(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        return jsonService().schemaBuilder.seb_setTypedArray(handle, type);
    }

    void seb_setEnumArray(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setEnumArray(handle, rawJson.data());
    }

    void seb_setDefault(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setDefault(handle, rawJson.data());
    }

    void seb_setMinimum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setMinimum(handle, rawJson.data());
    }

    void seb_setMaximum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setMaximum(handle, rawJson.data());
    }

    void seb_setDescription(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view description)
    {
        return jsonService().schemaBuilder.seb_setDescription(handle, description.data());
    }

    void seb_setTitle(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view title)
    {
        return jsonService().schemaBuilder.seb_setDefault(handle, title.data());
    }

    void seb_setReference(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view subSchemaName)
    {
        return jsonService().schemaBuilder.seb_setReference(handle, subSchemaName.data());
    }

}
