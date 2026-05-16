#include "services/errorservice.hpp"
#include "services/services.hpp"

#include "jsonservice_database.hpp"

using namespace Services;
using namespace ErrorService;

namespace JsonService
{
    const IJsonServiceTypes::EntryState getState(const IJsonServiceTypes::JsonTag tag)
    {
        const auto result = jsonService().database.getState(tag);
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonHandle get(const IJsonServiceTypes::JsonTag tag)
    {
        const auto result = jsonService().database.get(tag);
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonHandle getOrAdd(
        const IJsonServiceTypes::JsonTag tag,
        const void (* const creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    )
    {
        const auto result = jsonService().database.getOrAdd(tag, creator);
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonHandle getOrParse(const IJsonServiceTypes::JsonTag tag, const std::string_view json)
    {
        const auto result = jsonService().database.getOrParse(tag, json.data());
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::ModifiableJsonHandle declare(const IJsonServiceTypes::JsonTag tag)
    {
        const auto result = jsonService().database.declare(tag);
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonHandle commit(const IJsonServiceTypes::JsonTag tag)
    {
        const auto result = jsonService().database.commit(tag);
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonHandle parseValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::string_view json,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        const auto result = jsonService().database.parseValidatePatchAndAdd(tag, json.data(), validationSchemaTag);
        rethrowHostError();
        return result;
    }

    const IJsonServiceTypes::JsonHandle readValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::filesystem::path& file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        const auto result = jsonService().database.readValidatePatchAndAdd(tag, file.c_str(), validationSchemaTag);
        rethrowHostError();
        return result;
    }
}
