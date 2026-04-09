#ifndef JSONSERVICE_SCHEMABUILDER_DLX_HPP
#define JSONSERVICE_SCHEMABUILDER_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle        HOST_API_CALL instantiateSchemaBuilder_dlx(const char* const name = nullptr);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL instantiateSchemaElementBuilder_dlx(const char* const name);

    void HOST_API_CALL freeSchemaBuilder_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle& handle);
    void HOST_API_CALL freeSchemaElementBuilder_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle);

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void HOST_API_CALL sb_setAdditionalProperties(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const additionalProperties
    );
    void HOST_API_CALL sb_addRequired(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const required
    );

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL sb_addElementByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );
    void HOST_API_CALL sb_addElementByParseable(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name,
        const char* const rawJson
    );

    void HOST_API_CALL sb_addReferenceByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName,
        const IJsonServiceTypes::JsonType propertyType = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );
    void HOST_API_CALL sb_addReferenceByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );

    IJsonServiceTypes::JsonSchemaBuilderHandle HOST_API_CALL sb_addSubSchemaByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );
    void HOST_API_CALL sb_addSubSchemaByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    );

    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL sb_addPropertyByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName
    );
    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL sb_addPropertyByNameWithType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        IJsonServiceTypes::JsonType propertyType
    );

    IJsonServiceTypes::JsonHandle HOST_API_CALL sb_buildAndAdd(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    );

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder
}

#endif // JSONSERVICE_SCHEMABUILDER_DLX_HPP
