#ifndef IJSONSERVICE_SCHEMABUILDER_HPP
#define IJSONSERVICE_SCHEMABUILDER_HPP

#include <CallingConventions.hpp>

#include "IJsonService_Types.hpp"

struct IJsonService_SchemaBuilder
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle(*const HOST_API_CALL instantiateSchemaBuilder)(const char* const name);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle(*const HOST_API_CALL instantiateSchemaElementBuilder)(const char* const name);

    void (*const HOST_API_CALL freeSchemaBuilder)(IJsonServiceTypes::JsonSchemaBuilderHandle& handle);
    void (*const HOST_API_CALL freeSchemaElementBuilder)(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle);

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
    void (*const HOST_API_CALL sb_addAllOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL sb_addAnyOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL sb_addOneOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL sb_addNoneOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
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

    const char* const(*const HOST_API_CALL seb_getName)(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);
    IJsonServiceTypes::ModifiableJsonHandle(*const HOST_API_CALL seb_getJson)(
        const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle
    );

    void (*const HOST_API_CALL seb_setJsonByHandle)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonHandle json
    );
    void (*const HOST_API_CALL seb_setJsonByParseable)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );

    void (*const HOST_API_CALL seb_setProperty)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const propertyName,
        const char* const rawJson
    );
    void (*const HOST_API_CALL seb_setType)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void (*const HOST_API_CALL seb_setEnum)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL seb_setTypedArray)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void (*const HOST_API_CALL seb_setEnumArray)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL seb_setDefault)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL seb_setMinimum)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL seb_setMaximum)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (*const HOST_API_CALL seb_setDescription)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const description
    );
    void (*const HOST_API_CALL seb_setTitle)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const title
    );
    void (*const HOST_API_CALL seb_setReference)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const subSchemaName
    );
};

#endif // IJSONSERVICE_SCHEMABUILDER_HPP
