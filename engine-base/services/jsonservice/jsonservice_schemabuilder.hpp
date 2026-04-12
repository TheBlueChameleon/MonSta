#ifndef JSONSERVICE_SCHEMABUILDER_HPP
#define JSONSERVICE_SCHEMABUILDER_HPP

#include <filesystem>

#include <string_view>
#include <services/IJsonService.hpp>

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle        instantiateSchemaBuilder(const std::string_view name);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle instantiateSchemaElementBuilder(const std::string_view name);

    void freeSchemaBuilder(IJsonServiceTypes::JsonSchemaBuilderHandle& handle);
    void freeSchemaElementBuilder(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle);

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void sb_setAdditionalProperties(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view additionalProperties
    );

    void sb_addRequired(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view required
    );
    void sb_addAllOfReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    );
    void sb_addAnyOfReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    );
    void sb_addOneOfReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    );
    void sb_addNotReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    );

    IJsonServiceTypes::ModifiableJsonHandle sb_addElementByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name
    );
    void sb_addElementByParseable(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name,
        const std::string_view rawJson
    );

    void sb_addReferenceByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view schemaName,
        const IJsonServiceTypes::JsonType propertyType = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );
    void sb_addReferenceByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );

    IJsonServiceTypes::JsonSchemaBuilderHandle sb_addSubSchemaByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    );
    void sb_addSubSchemaByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    );

    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName
    );
    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByNameWithType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        IJsonServiceTypes::JsonType propertyType
    );

    IJsonServiceTypes::JsonHandle sb_buildAndAdd(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    );

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder

    const std::string_view seb_getName(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);
    IJsonServiceTypes::ModifiableJsonHandle seb_getJson(
        const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle
    );

    void seb_setJsonByHandle(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonHandle json
    );
    void seb_setJsonByParseable(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view rawJson
    );

    void seb_setProperty(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view rawJson
    );
    void seb_setType(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void seb_setTypedArray(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void seb_setEnum(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view rawJson
    );
    void seb_setDescription(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view description
    );
    void seb_setTitle(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view title
    );
    void seb_setDefault(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view rawJson
    );
    void seb_setMinimum(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view rawJson
    );
    void seb_setMaximum(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view rawJson
    );
}

#endif // JSONSERVICE_SCHEMABUILDER_HPP
