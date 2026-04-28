#ifndef IJSONSERVICE_DATABASE_HPP
#define IJSONSERVICE_DATABASE_HPP

#include <CallingConventions.hpp>

#include "IJsonService_Types.hpp"

struct IJsonService_Database
{
    const IJsonServiceTypes::EntryState(HOST_API_CALL* const getState)(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const get)(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const getOrAdd)(
        const IJsonServiceTypes::JsonTag tag,
        const void(HOST_API_CALL* const creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    );
    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const getOrParse)(
        const IJsonServiceTypes::JsonTag tag,
        const char* const json
    );
    const IJsonServiceTypes::ModifiableJsonHandle(HOST_API_CALL* const declare)(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const commit)(const IJsonServiceTypes::JsonTag tag);

    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const parseValidatePatchAndAdd)(
        const IJsonServiceTypes::JsonTag    tag,
        const char* const                   json,
        const IJsonServiceTypes::JsonTag    validationSchemaTag
    );
    const IJsonServiceTypes::JsonHandle(HOST_API_CALL* const readValidatePatchAndAdd)(
        const IJsonServiceTypes::JsonTag    tag,
        const char* const                   file,
        const IJsonServiceTypes::JsonTag    validationSchemaTag
    );

};

#endif // IJSONSERVICE_DATABASE_HPP
