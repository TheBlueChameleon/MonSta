#ifndef JSONSERVICE_DLX_HPP
#define JSONSERVICE_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // JsonDatabase

    const HOST_API_CALL IJsonService::EntryState getState_dlx(const IJsonService::JsonTag tag);
    const HOST_API_CALL IJsonService::JsonHandle get_dlx(const IJsonService::JsonTag tag);
    const HOST_API_CALL IJsonService::JsonHandle getOrAdd_dlx(
        const IJsonService::JsonTag tag,
        const void(*creator)(const IJsonService::ModifiableJsonHandle)
    );
    const HOST_API_CALL IJsonService::JsonHandle getOrParse_dlx(
        const IJsonService::JsonTag tag,
        const char* const json
    );
    const HOST_API_CALL IJsonService::ModifiableJsonHandle declare_dlx(const IJsonService::JsonTag tag);
    const HOST_API_CALL IJsonService::JsonHandle commit_dlx(const IJsonService::JsonTag tag);

    // ---------------------------------------------------------------------- //
    // Json compatibility layer

    const HOST_API_CALL IJsonService::JsonHandle navigateTo_dlx(const IJsonService::JsonHandle handle, const char* const jsonPointer);
    const bool HOST_API_CALL contains_dlx(const IJsonService::JsonHandle handle, const char* const elementName);

    const IJsonService::JsonType HOST_API_CALL getType_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isNull_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isBoolean_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isInteger_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isUnsigned_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isFloat_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isString_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isArray_dlx(const IJsonService::JsonHandle handle);
    const bool HOST_API_CALL isObject_dlx(const IJsonService::JsonHandle handle);

    const bool HOST_API_CALL getAsBool_dlx(const IJsonService::JsonHandle handle);
    const int HOST_API_CALL getAsInteger_dlx(const IJsonService::JsonHandle handle);
    const unsigned long long HOST_API_CALL getAsUnsigned_dlx(const IJsonService::JsonHandle handle);
    const double HOST_API_CALL getAsFloat_dlx(const IJsonService::JsonHandle handle);
    const char* const HOST_API_CALL getAsString_dlx(const IJsonService::JsonHandle handle);

    const int HOST_API_CALL getArraySize_dlx(const IJsonService::JsonHandle handle);
    const IJsonService::JsonHandle HOST_API_CALL getArrayItem_dlx(const IJsonService::JsonHandle handle, const int index);

    void HOST_API_CALL setToNull_dlx(const IJsonService::ModifiableJsonHandle handle);
    void HOST_API_CALL setToBool_dlx(const IJsonService::ModifiableJsonHandle handle, const bool value);
    void HOST_API_CALL setToInteger_dlx(const IJsonService::ModifiableJsonHandle handle, const int value);
    void HOST_API_CALL setToUnsigned_dlx(const IJsonService::ModifiableJsonHandle handle, const unsigned value);
    void HOST_API_CALL setToFloat_dlx(const IJsonService::ModifiableJsonHandle handle, const double value);
    void HOST_API_CALL setToString_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const value);
    void HOST_API_CALL setToHandle_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void HOST_API_CALL setToArray_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void HOST_API_CALL setToObject_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void HOST_API_CALL setToParseable_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const source);

    // ---------------------------------------------------------------------- //
    // Parsing & Validation

    /* TODO:
     * read without validation?
     */

    const IJsonService::JsonHandle HOST_API_CALL parseValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag     tag,
        const char* const               json,
        const IJsonService::JsonTag     validationSchemaTag
    );
    const IJsonService::JsonHandle HOST_API_CALL readAndAdd_dlx(
        const IJsonService::JsonTag tag,
        const char* const file
    );
    const IJsonService::JsonHandle HOST_API_CALL readValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag tag,
        const char* const file,
        const IJsonService::JsonTag validationSchemaTag
    );

    // ---------------------------------------------------------------------- //
    // Schema Builder Operations

    const IJsonService::JsonSchemaBuilderHandle    HOST_API_CALL instantiateSchemaBuilder_dlx();
    const IJsonService::JsonSubSchemaBuilderHandle HOST_API_CALL instantiateSubSchemaBuilder_dlx();
    const IJsonService::JsonElementBuilderHandle   HOST_API_CALL instantiateElementBuilder_dlx();

    void HOST_API_CALL freeSchemaBuilder_dlx(const IJsonService::JsonSchemaBuilderHandle*);
    void HOST_API_CALL freeSubSchemaBuilder_dlx(const IJsonService::JsonSubSchemaBuilderHandle*);
    void HOST_API_CALL freeElementBuilder_dlx(const IJsonService::JsonElementBuilderHandle*);

    /*
     * json schema builder ops:
     * ???
     */
}

#endif // JSONSERVICE_DLX_HPP
