#ifndef JSONSERVICE_DATABASE_DLX_H
#define JSONSERVICE_DATABASE_DLX_H

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // JsonDatabase

    const IJsonServiceTypes::EntryState HOST_API_CALL getState_dlx(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle HOST_API_CALL get_dlx(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle HOST_API_CALL getOrAdd_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const void(*creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    );
    const IJsonServiceTypes::JsonHandle HOST_API_CALL getOrParse_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const char* const json
    );
    const IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL declare_dlx(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle HOST_API_CALL commit_dlx(const IJsonServiceTypes::JsonTag tag);

    // ---------------------------------------------------------------------- //
    // Parsing & Validation

    const IJsonServiceTypes::JsonHandle HOST_API_CALL parseValidatePatchAndAdd_dlx(
        const IJsonServiceTypes::JsonTag    tag,
        const char* const                   json,
        const IJsonServiceTypes::JsonTag    validationSchemaTag
    );
    const IJsonServiceTypes::JsonHandle HOST_API_CALL readAndAdd_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const char* const file
    );
    const IJsonServiceTypes::JsonHandle HOST_API_CALL readValidatePatchAndAdd_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const char* const file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    );
}

#endif // JSONSERVICE_DATABASE_DLX_H
