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

    void HOST_API_CALL setAdditionalProperties(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const additionalProperties
    );
    void HOST_API_CALL addRequired(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const required
    );

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL addElement(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );

    void HOST_API_CALL addReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName,
        const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );
    void HOST_API_CALL addReference(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );

    IJsonServiceTypes::JsonSchemaBuilderHandle HOST_API_CALL addSubSchema(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );
    void HOST_API_CALL addSubSchema(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
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

    IJsonServiceTypes::JsonHandle buildAndCommit(const char* const tag) const;

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder
}

#endif // JSONSERVICE_SCHEMABUILDER_DLX_HPP
