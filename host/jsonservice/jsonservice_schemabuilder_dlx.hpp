#ifndef JSONSERVICE_SCHEMABUILDER_DLX_HPP
#define JSONSERVICE_SCHEMABUILDER_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    IJsonServiceTypes::JsonSchemaBuilderHandle        HOST_API_CALL instantiateSchemaBuilder_dlx();
    IJsonServiceTypes::JsonSubSchemaBuilderHandle     HOST_API_CALL instantiateSubSchemaBuilder_dlx(const char* const name);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL instantiateSchemaElementBuilder_dlx(const char* const name);

    void HOST_API_CALL freeSchemaBuilder_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle& handle);
    void HOST_API_CALL freeSubSchemaBuilder_dlx(IJsonServiceTypes::JsonSubSchemaBuilderHandle& handle);
    void HOST_API_CALL freeSchemaElementBuilder_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle);

    // ---------------------------------------------------------------------- //
    // JonsSchemaBuilder

    void HOST_API_CALL setAdditionalProperties(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const additionalProperties
    );
    void HOST_API_CALL addRequired(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const required
    );

    void HOST_API_CALL addReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName
    );
    void HOST_API_CALL addReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name,
        const IJsonServiceTypes::JsonSubSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );

    IJsonServiceTypes::JsonSubSchemaBuilderHandle HOST_API_CALL addSubSchema(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );
    void HOST_API_CALL addSubSchema(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSubSchemaBuilderHandle subSchema
    );

    void HOST_API_CALL addProperty(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );
    void HOST_API_CALL addProperty(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name,
        IJsonServiceTypes::JsonType type
    );

    // ---------------------------------------------------------------------- //
    // JonsSchemaBuilder
}

#endif // JSONSERVICE_SCHEMABUILDER_DLX_HPP
