#ifndef JSONSERVICE_DATABASE_HPP
#define JSONSERVICE_DATABASE_HPP

#include <filesystem>
#include <string_view>

#include <services/IJsonService.hpp>

namespace JsonService
{
    const IJsonServiceTypes::EntryState getState(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle get(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle getOrAdd(
        const IJsonServiceTypes::JsonTag tag,
        const void(*const HOST_API_CALL creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    );
    const IJsonServiceTypes::JsonHandle getOrParse(
        const IJsonServiceTypes::JsonTag tag,
        const std::string_view json
    );
    const IJsonServiceTypes::ModifiableJsonHandle declare(const IJsonServiceTypes::JsonTag tag);
    const IJsonServiceTypes::JsonHandle commit(const IJsonServiceTypes::JsonTag tag);

    const IJsonServiceTypes::JsonHandle parseValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag    tag,
        const std::string_view              json,
        const IJsonServiceTypes::JsonTag    validationSchemaTag
    );
    const IJsonServiceTypes::JsonHandle readValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag    tag,
        const std::filesystem::path&        file,
        const IJsonServiceTypes::JsonTag    validationSchemaTag
    );
}

#endif // JSONSERVICE_DATABASE_HPP
