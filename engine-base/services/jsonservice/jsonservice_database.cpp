#include "services/services.hpp"

#include "jsonservice_database.hpp"

namespace JsonService
{
    const IJsonServiceTypes::EntryState getState(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.getState(tag);
    }

    const IJsonServiceTypes::JsonHandle get(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.get(tag);
    }

    const IJsonServiceTypes::JsonHandle getOrAdd(
        const IJsonServiceTypes::JsonTag tag,
        const void (* const creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    )
    {
        return jsonService().database.getOrAdd(tag, creator);
    }

    const IJsonServiceTypes::JsonHandle getOrParse(const IJsonServiceTypes::JsonTag tag, const std::string_view json)
    {
        return jsonService().database.getOrParse(tag, json.data());
    }

    const IJsonServiceTypes::ModifiableJsonHandle declare(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.declare(tag);
    }

    const IJsonServiceTypes::JsonHandle commit(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.commit(tag);
    }

    const IJsonServiceTypes::JsonHandle parseValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::string_view json,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        return jsonService().database.parseValidatePatchAndAdd(tag, json.data(), validationSchemaTag);
    }

    const IJsonServiceTypes::JsonHandle readValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::filesystem::__cxx11::path& file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        return jsonService().database.readValidatePatchAndAdd(tag, file.c_str(), validationSchemaTag);
    }
}
