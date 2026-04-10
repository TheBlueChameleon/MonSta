#ifndef IJSONSERVICE_SCHEMABUILDER_HPP
#define IJSONSERVICE_SCHEMABUILDER_HPP

#include <CallingConventions.hpp>

#include "IJsonService_Types.hpp"

struct IJsonService_SchemaBuilder
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle(*const HOST_API_CALL instantiateSchemaBuilder_dlx)(const char* const name);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle(*const HOST_API_CALL instantiateSchemaElementBuilder_dlx)(const char* const name);

    void (*const HOST_API_CALL freeSchemaBuilder_dlx)(IJsonServiceTypes::JsonSchemaBuilderHandle& handle);
    void (*const HOST_API_CALL freeSchemaElementBuilder_dlx)(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle);

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void (*const HOST_API_CALL sb_setAdditionalProperties)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const additionalProperties
    );

    void (*const HOST_API_CALL sb_addRequired)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const required
    );
    void (*const HOST_API_CALL sb_addAllOfReference_dlx)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );
    void (*const HOST_API_CALL sb_addAnyOfReference_dlx)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );
    void (*const HOST_API_CALL sb_addOneOfReference_dlx)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );
    void (*const HOST_API_CALL sb_addNotReference_dlx)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );

    IJsonServiceTypes::ModifiableJsonHandle(*const HOST_API_CALL sb_addElementByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );
    void(*const HOST_API_CALL sb_addElementByParseable)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name,
        const char* const rawJson
    );

    void (*const HOST_API_CALL sb_addReferenceByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    );
    void (*const HOST_API_CALL sb_addReferenceByType)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    );

    IJsonServiceTypes::JsonSchemaBuilderHandle(*const HOST_API_CALL sb_addSubSchemaByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );
    void (*const HOST_API_CALL sb_addSubSchemaByType)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    );

    IJsonServiceTypes::JsonSchemaElementBuilderHandle(*const HOST_API_CALL sb_addPropertyByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName
    );
    IJsonServiceTypes::JsonSchemaElementBuilderHandle(*const HOST_API_CALL sb_addPropertyByNameWithType)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        IJsonServiceTypes::JsonType propertyType
    );

    IJsonServiceTypes::JsonHandle(*const HOST_API_CALL sb_buildAndAdd)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    );

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder
};

#endif // IJSONSERVICE_SCHEMABUILDER_HPP
