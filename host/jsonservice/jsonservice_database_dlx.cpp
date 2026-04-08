#include <nlohmann/json.hpp>

#include <services/IJsonService.hpp>

#include "errorservice/catchmacros.hpp"

#include "handleconverter.hpp"
#include "jsonservice.hpp"
#include "jsonservice_database_dlx.hpp"

using namespace nlohmann;

namespace JsonService
{
    // ====================================================================== //
    // JsonDatabase

    const IJsonServiceTypes::EntryState HOST_API_CALL getState_dlx(const IJsonServiceTypes::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return getState(tag);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::EntryState::ERROR)
        CATCH_STD_EXCEPTION(IJsonServiceTypes::EntryState::ERROR)
    }

    const IJsonServiceTypes::JsonHandle HOST_API_CALL get_dlx(const IJsonServiceTypes::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return toJsonHandle(get(tag));
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle(nullptr))
    }

    const IJsonServiceTypes::JsonHandle HOST_API_CALL getOrAdd_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const void(*creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    )
    {
        try
        {
            assertSaneTag(tag);
            if (creator == nullptr)
            {
                ErrorService::setError(ApiStatusCode::INVALID_REQUEST_BY_CLIENT, "Client attempted getOrAdd with null creator");
                return IJsonServiceTypes::JsonHandle(nullptr);
            }

            auto convertedCreator = [&creator](ordered_json& json)
            {
                creator(toModifiableJsonHandle(json));
            };

            return toJsonHandle(getOrAdd(tag, convertedCreator));
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle(nullptr))
    }

    const IJsonServiceTypes::JsonHandle HOST_API_CALL getOrParse_dlx(const IJsonServiceTypes::JsonTag tag, const char* const json)
    {
        try
        {
            assertSaneTag(tag);
            assertNonNullParseable(json);
            return toJsonHandle(
                       getOrAdd(tag, parse(json))
                   );
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle(nullptr))

    }

    const IJsonServiceTypes::ModifiableJsonHandle HOST_API_CALL declare_dlx(const IJsonServiceTypes::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            std::optional<std::reference_wrapper<ordered_json>> opt = declare(tag);
            if (opt.has_value())
            {
                return toModifiableJsonHandle(opt.value());
            }
            else
            {
                return IJsonServiceTypes::ModifiableJsonHandle(nullptr);
            }

        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::ModifiableJsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::ModifiableJsonHandle(nullptr))
    }

    const IJsonServiceTypes::JsonHandle HOST_API_CALL commit_dlx(const IJsonServiceTypes::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return toJsonHandle(getDatabase().commit(tag));
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle(nullptr))
    }

    // ====================================================================== //
    // Parsing & Validation

    const IJsonServiceTypes::JsonHandle HOST_API_CALL parseValidatePatchAndAdd_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const char* const json,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        try
        {
            assertNonNullParseable(json);
            return toJsonHandle(
                       validatePatchAndAdd(
                           tag,
                           parse(json),
                           get(validationSchemaTag)
                       )
                   );
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle(nullptr))
    }

    const IJsonServiceTypes::JsonHandle HOST_API_CALL readAndAdd_dlx(const IJsonServiceTypes::JsonTag tag, const char* const file)
    {
        try
        {
            assertNonNullFilename(file);
            return toJsonHandle(
                       readAndAdd(tag, file)
                   );
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle(nullptr))
    }

    const IJsonServiceTypes::JsonHandle HOST_API_CALL readValidatePatchAndAdd_dlx(
        const IJsonServiceTypes::JsonTag tag,
        const char* const file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        try
        {
            assertNonNullFilename(file);
            return toJsonHandle(
                       readValidateByTagPatchAndAdd(
                           tag,
                           file,
                           validationSchemaTag
                       )
                   );
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonHandle(nullptr))
    }

}
