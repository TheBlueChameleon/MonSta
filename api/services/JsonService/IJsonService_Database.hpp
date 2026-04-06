#ifndef IJSONSERVICE_DATABASE_HPP
#define IJSONSERVICE_DATABASE_HPP

#include <CallingConventions.hpp>

#include "IJsonService_Types.hpp"

struct IJsonService_Database
{
    const IJsonServiceTypes::EntryState(*const HOST_API_CALL getState)(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL get)(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL getOrAdd)(
        const IJsonServiceTypes::JsonTag tag,
        const void(*const HOST_API_CALL creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    );
    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL getOrParse)(
        const IJsonServiceTypes::JsonTag tag,
        const char* const json
    );
    const IJsonServiceTypes::ModifiableJsonHandle(*const HOST_API_CALL declare)(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL commit)(const IJsonServiceTypes::JsonTag tag);

    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL parseValidatePatchAndAdd)(
        const IJsonServiceTypes::JsonTag    tag,
        const char* const                   json,
        const IJsonServiceTypes::JsonTag    validationSchemaTag
    );
    const IJsonServiceTypes::JsonHandle(*const HOST_API_CALL readValidatePatchAndAdd)(
        const IJsonServiceTypes::JsonTag    tag,
        const char* const                   file,
        const IJsonServiceTypes::JsonTag    validationSchemaTag
    );

};

#endif // IJSONSERVICE_DATABASE_HPP
