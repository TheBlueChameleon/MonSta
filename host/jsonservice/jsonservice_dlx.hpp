#ifndef JSONSERVICE_DLX_HPP
#define JSONSERVICE_DLX_HPP

#include <services/IJsonService.hpp>

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // JsonDatabase

    const IJsonService::EntryState getState_dlx(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle get_dlx(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle getOrAdd_dlx(
        const IJsonService::JsonTag tag,
        const void(*creator)(const IJsonService::ModifiableJsonHandle)
    );
    const IJsonService::JsonHandle getOrParse_dlx(
        const IJsonService::JsonTag tag,
        const char* const json
    );
    const IJsonService::ModifiableJsonHandle declare_dlx(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle commit_dlx(const IJsonService::JsonTag tag);

    // ---------------------------------------------------------------------- //
    // Json compatibility layer

    const IJsonService::JsonHandle navigateTo_dlx(const IJsonService::JsonHandle handle, const char* const jsonPointer);
    const bool contains_dlx(const IJsonService::JsonHandle handle, const char* const elementName);

    const IJsonService::JsonType getType_dlx(const IJsonService::JsonHandle handle);
    const bool isNull_dlx(const IJsonService::JsonHandle handle);
    const bool isBoolean_dlx(const IJsonService::JsonHandle handle);
    const bool isInteger_dlx(const IJsonService::JsonHandle handle);
    const bool isUnsigned_dlx(const IJsonService::JsonHandle handle);
    const bool isFloat_dlx(const IJsonService::JsonHandle handle);
    const bool isString_dlx(const IJsonService::JsonHandle handle);
    const bool isArray_dlx(const IJsonService::JsonHandle handle);
    const bool isObject_dlx(const IJsonService::JsonHandle handle);

    const bool getAsBool_dlx(const IJsonService::JsonHandle handle);
    const int getAsInteger_dlx(const IJsonService::JsonHandle handle);
    const unsigned long long getAsUnsigned_dlx(const IJsonService::JsonHandle handle);
    const double getAsFloat_dlx(const IJsonService::JsonHandle handle);
    const char* const getAsString_dlx(const IJsonService::JsonHandle handle);

    const int getArraySize_dlx(const IJsonService::JsonHandle handle);
    const IJsonService::JsonHandle getArrayItem_dlx(const IJsonService::JsonHandle handle, const int index);

    void setToNull_dlx(const IJsonService::ModifiableJsonHandle handle);
    void setToBool_dlx(const IJsonService::ModifiableJsonHandle handle, const bool value);
    void setToInteger_dlx(const IJsonService::ModifiableJsonHandle handle, const int value);
    void setToUnsigned_dlx(const IJsonService::ModifiableJsonHandle handle, const unsigned value);
    void setToFloat_dlx(const IJsonService::ModifiableJsonHandle handle, const double value);
    void setToString_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const value);
    void setToHandle_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void setToArray_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void setToObject_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void setToParseable_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const source);

    // ---------------------------------------------------------------------- //
    // Parsing & Validation

    /* TODO:
     * read without validation?
     * rewrite existing with underlying getOrAdd?
     */

    const IJsonService::JsonHandle parseValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag     tag,
        const char* const               json,
        const IJsonService::JsonTag     validationSchemaTag
    );
    const IJsonService::JsonHandle readValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag tag,
        const char* const file,
        const IJsonService::JsonTag validationSchemaTag
    );

    // ---------------------------------------------------------------------- //
    // Schema Builder Operations

    const IJsonService::JsonSchemaBuilderHandle    instantiateSchemaBuilder_dlx();
    const IJsonService::JsonSubSchemaBuilderHandle instantiateSubSchemaBuilder_dlx();
    const IJsonService::JsonElementBuilderHandle   instantiateElementBuilder_dlx();

    void freeSchemaBuilder_dlx(const IJsonService::JsonSchemaBuilderHandle*);
    void freeSubSchemaBuilder_dlx(const IJsonService::JsonSubSchemaBuilderHandle*);
    void freeElementBuilder_dlx(const IJsonService::JsonElementBuilderHandle*);

    /*
     * json schema builder ops:
     * ???
     */
}

#endif // JSONSERVICE_DLX_HPP
