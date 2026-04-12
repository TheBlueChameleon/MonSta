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

    void HOST_API_CALL sb_setAdditionalProperties_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const additionalProperties
    );

    void HOST_API_CALL sb_addRequired_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const required
    );
    void HOST_API_CALL sb_addAllOfRequirement_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL sb_addAnyOfRequirement_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL sb_addOneOfRequirement_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL sb_addNoneOfRequirement_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const rawJson
    );

    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL sb_addElementByName_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name
    );
    void HOST_API_CALL sb_addElementByParseable_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const name,
        const char* const rawJson
    );

    void HOST_API_CALL sb_addReferenceByName_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const char* const schemaName,
        const IJsonServiceTypes::JsonType propertyType = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );
    void HOST_API_CALL sb_addReferenceByType_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType = IJsonServiceTypes::JsonType::OBJECT,
        bool setDefaults = true
    );

    IJsonServiceTypes::JsonSchemaBuilderHandle HOST_API_CALL sb_addSubSchemaByName_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const schemaName
    );
    void HOST_API_CALL sb_addSubSchemaByType_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    );

    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL sb_addPropertyByName_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName
    );
    IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL sb_addPropertyByNameWithType_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const char* const propertyName,
        IJsonServiceTypes::JsonType propertyType
    );

    IJsonServiceTypes::JsonHandle HOST_API_CALL sb_buildAndAdd_dlx(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    );

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder

    const char* const HOST_API_CALL seb_getName_dlx(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);
    IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL seb_getJson_dlx(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);

    void HOST_API_CALL seb_setJsonByHandle_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonHandle json
    );
    void HOST_API_CALL seb_setJsonByParseable_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );

    void HOST_API_CALL seb_setProperty_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const propertyName,
        const char* const rawJson
    );
    void HOST_API_CALL seb_setType_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void HOST_API_CALL seb_setEnum_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL seb_setTypedArray_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const IJsonServiceTypes::JsonType type
    );
    void HOST_API_CALL seb_setEnumArray_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL seb_setDefault_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL seb_setMinimum_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL seb_setMaximum_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const rawJson
    );
    void HOST_API_CALL seb_setDescription_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const description
    );
    void HOST_API_CALL seb_setTitle_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const title
    );
    void HOST_API_CALL seb_setReference_dlx(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const char* const subSchemaName
    );
}

#endif // JSONSERVICE_SCHEMABUILDER_DLX_HPP
