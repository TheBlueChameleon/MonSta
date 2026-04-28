#ifndef IJSONSERVICE_SCHEMABUILDER_HPP
#define IJSONSERVICE_SCHEMABUILDER_HPP

#include <CallingConventions.hpp>

#include "IJsonService_Types.hpp"

struct IJsonService_SchemaBuilder
{
    // ---------------------------------------------------------------------- //
    // instantiate and free

    IJsonServiceTypes::JsonSchemaBuilderHandle(HOST_API_CALL* const instantiateSchemaBuilder)(const char* const name);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle(HOST_API_CALL* const instantiateSchemaElementBuilder)(const char* const name);

    void (HOST_API_CALL* const freeSchemaBuilder)(IJsonServiceTypes::JsonSchemaBuilderHandle* handle);
    void (HOST_API_CALL* const freeSchemaElementBuilder)(IJsonServiceTypes::JsonSchemaElementBuilderHandle* handle);

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void (HOST_API_CALL* const sb_setAdditionalProperties)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const additionalProperties
    );

    void (HOST_API_CALL* const sb_addRequired)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const required
    );
    void (HOST_API_CALL* const sb_addAllOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const sb_addAnyOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const sb_addOneOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const sb_addNoneOfRequirement)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );

    IJsonServiceTypes::ModifiableJsonHandle(HOST_API_CALL* const sb_addElementByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );
    void(HOST_API_CALL* const sb_addElementByParseable)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name,
        const char* const rawJson
    );

    void (HOST_API_CALL* const sb_addReferenceByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    );
    void (HOST_API_CALL* const sb_addReferenceByType)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    );

    IJsonServiceTypes::JsonSchemaBuilderHandle(HOST_API_CALL* const sb_addSubSchemaByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );
    void (HOST_API_CALL* const sb_addSubSchemaByType)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    );

    IJsonServiceTypes::JsonSchemaElementBuilderHandle(HOST_API_CALL* const sb_addPropertyByName)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName
    );
    IJsonServiceTypes::JsonSchemaElementBuilderHandle(HOST_API_CALL* const sb_addPropertyByNameWithType)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        IJsonServiceTypes::JsonType propertyType
    );

    IJsonServiceTypes::JsonHandle(HOST_API_CALL* const sb_buildAndAdd)(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    );

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder

    const char* const(HOST_API_CALL* const seb_getName)(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);
    IJsonServiceTypes::ModifiableJsonHandle(*const HOST_API_CALL seb_getJson)(
        const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle
    );

    void (HOST_API_CALL* const seb_setJsonByHandle)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonHandle json
    );
    void (HOST_API_CALL* const seb_setJsonByParseable)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );

    void (HOST_API_CALL* const seb_setProperty)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const propertyName,
        const char* const rawJson
    );
    void (HOST_API_CALL* const seb_setType)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void (HOST_API_CALL* const seb_setEnum)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const seb_setTypedArray)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void (HOST_API_CALL* const seb_setEnumArray)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const seb_setDefault)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const seb_setMinimum)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const seb_setMaximum)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void (HOST_API_CALL* const seb_setDescription)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const description
    );
    void (HOST_API_CALL* const seb_setTitle)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const title
    );
    void (HOST_API_CALL* const seb_setReference)(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const subSchemaName
    );
};

#endif // IJSONSERVICE_SCHEMABUILDER_HPP
