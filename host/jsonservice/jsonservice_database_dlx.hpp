#ifndef JSONSERVICE_DATABASE_DLX_H
#define JSONSERVICE_DATABASE_DLX_H

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // JsonDatabase

    const HOST_API_CALL IJsonServiceTypes::EntryState getState_dlx(const IJsonServiceTypes::JsonTag tag);
    const HOST_API_CALL IJsonServiceTypes::JsonHandle get_dlx(const IJsonServiceTypes::JsonTag tag);
    const HOST_API_CALL IJsonServiceTypes::JsonHandle getOrAdd_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const void(*creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    );
    const HOST_API_CALL IJsonServiceTypes::JsonHandle getOrParse_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const char* const json
    );
    const HOST_API_CALL IJsonServiceTypes::ModifiableJsonHandle declare_dlx(const IJsonServiceTypes::JsonTag tag);
    const HOST_API_CALL IJsonServiceTypes::JsonHandle commit_dlx(const IJsonServiceTypes::JsonTag tag);

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
