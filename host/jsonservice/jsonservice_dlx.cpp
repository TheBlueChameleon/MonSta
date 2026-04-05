#include <services/IJsonService.hpp>

#include "errorservice/catchmacros.hpp"

#include "handleconverter.hpp"
#include "jsonservice.hpp"
#include "jsonservice_dlx.hpp"

using namespace nlohmann;

namespace JsonService
{
    // ====================================================================== //
    // JsonDatabase

    const IJsonService::EntryState getState_dlx(const IJsonService::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return getState(tag);
        }
        CATCH_ABSTRACT_ERROR(IJsonService::EntryState::ERROR)
        CATCH_STD_EXCEPTION(IJsonService::EntryState::ERROR)
    }

    const IJsonService::JsonHandle get_dlx(const IJsonService::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return toJsonHandle(get(tag));
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    const IJsonService::JsonHandle getOrAdd_dlx(
        const IJsonService::JsonTag tag,
        const void(*creator)(const IJsonService::ModifiableJsonHandle)
    )
    {
        try
        {
            assertSaneTag(tag);
            if (creator == nullptr)
            {
                ErrorService::setError(ApiStatusCode::INVALID_REQUEST_BY_CLIENT, "Client attempted getOrAdd with null creator");
                return IJsonService::JsonHandle(nullptr);
            }

            auto convertedCreator = [&creator](ordered_json& json)
            {
                creator(toModifiableJsonHandle(json));
            };

            return toJsonHandle(getOrAdd(tag, convertedCreator));
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    const IJsonService::JsonHandle getOrParse_dlx(const IJsonService::JsonTag tag, const char* const json)
    {
        try
        {
            assertSaneTag(tag);
            return toJsonHandle(
                       getOrAdd(tag, parse(json))
                   );
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))

    }

    const IJsonService::ModifiableJsonHandle declare_dlx(const IJsonService::JsonTag tag)
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
                return IJsonService::ModifiableJsonHandle(nullptr);
            }

        }
        CATCH_ABSTRACT_ERROR(IJsonService::ModifiableJsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::ModifiableJsonHandle(nullptr))
    }

    const IJsonService::JsonHandle commit_dlx(const IJsonService::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return toJsonHandle(getDatabase().commit(tag));
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    // ====================================================================== //
    // Json compatibility layer

    const IJsonService::JsonHandle navigateTo_dlx(const IJsonService::JsonHandle handle, const char* const jsonPointer)
    {
        try
        {
            assertSaneHandle(handle);
            const auto& base = toOrderedJson(handle);

            assertSaneJsonPointer(jsonPointer);

            if (jsonPointer[0] == '/')
            {
                const auto jptr = ordered_json::json_pointer(jsonPointer);
                const ordered_json& target = base.at(jptr);
                return toJsonHandle(target);
            }
            else
            {
                const auto& target = base.at(jsonPointer);
                return toJsonHandle(target);
            }
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    const bool contains_dlx(const IJsonService::JsonHandle handle, const char* const elementName)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.contains(elementName);
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const IJsonService::JsonType getType_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return static_cast<IJsonService::JsonType>(base.type());
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonType::VOID)
        CATCH_STD_EXCEPTION(IJsonService::JsonType::VOID)
    }

    const bool isNull_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_null();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool isBoolean_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_boolean();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool isInteger_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_number_integer();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool isUnsigned_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_number_unsigned();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool isFloat_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_number_float();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool isString_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_string();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool isArray_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_array();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool isObject_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.is_object();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const bool getAsBool_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_boolean())
            {
                throw ClientRequestError("Client attempted to read non-boolean Json object as boolean");
            }
            return base.get<bool>();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const int getAsInteger_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_number_integer())
            {
                throw ClientRequestError("Client attempted to read non-integer Json object as integer");
            }
            return base.get<int>();
        }
        CATCH_ABSTRACT_ERROR(0)
        CATCH_STD_EXCEPTION(0)
    }

    const unsigned long long getAsUnsigned_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_number_unsigned())
            {
                throw ClientRequestError("Client attempted to read non-unsigned Json object as unsigned");
            }
            return base.get<unsigned long long>();
        }
        CATCH_ABSTRACT_ERROR(0)
        CATCH_STD_EXCEPTION(0)
    }

    const double getAsFloat_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_number_float())
            {
                throw ClientRequestError("Client attempted to read non-float Json object as float");
            }
            return base.get<double>();
        }
        CATCH_ABSTRACT_ERROR(false)
        CATCH_STD_EXCEPTION(false)
    }

    const char* const getAsString_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_string())
            {
                throw ClientRequestError("Client attempted to read non-string Json object as string");
            }
            const auto ptr = base.get_ptr<const ordered_json::string_t*>();
            return ptr->data();
        }
        CATCH_ABSTRACT_ERROR("")
        CATCH_STD_EXCEPTION("")
    }

    const int getArraySize_dlx(const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            return base.size();
        }
        CATCH_ABSTRACT_ERROR(-1)
        CATCH_STD_EXCEPTION(-1)
    }

    const IJsonService::JsonHandle getArrayItem_dlx(const IJsonService::JsonHandle handle, const int index)
    {
        try
        {
            assertSaneHandle(handle);
            const ordered_json& base = toOrderedJson(handle);
            if (!base.is_array())
            {
                ErrorService::setError(
                    ApiStatusCode::INVALID_REQUEST_BY_CLIENT,
                    "Client attempted array operation on non-array Json element"
                );
                return IJsonService::JsonHandle(nullptr);
            }
            if (index < 0 ||index >= base.size())
            {
                ErrorService::setError(
                    ApiStatusCode::INVALID_REQUEST_BY_CLIENT,
                    "Client attempted array operation with out-of-bounds index "s +
                    std::to_string(index)
                );
                return IJsonService::JsonHandle(nullptr);
            }

            return toJsonHandle(base.at(index));
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    void setToNull_dlx(const IJsonService::ModifiableJsonHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = ordered_json();
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void setToBool_dlx(const IJsonService::ModifiableJsonHandle handle, const bool value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void setToInteger_dlx(const IJsonService::ModifiableJsonHandle handle, const int value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void setToUnsigned_dlx(const IJsonService::ModifiableJsonHandle handle, const unsigned int value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void setToFloat_dlx(const IJsonService::ModifiableJsonHandle handle, const double value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void setToString_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const value)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = value;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void setToHandle_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source)
    {
        try
        {
            assertSaneHandle(source);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = toOrderedJson(source);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_STD_EXCEPTION()
    }

    // TODO: maybe type check source is Array?
    void setToArray_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source)
    {
        setToHandle_dlx(handle, source);
    }

    // TODO: maybe type check source is Object?
    void setToObject_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source)
    {
        setToHandle_dlx(handle, source);
    }

    void setToParseable_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const source)
    {
        try
        {
            assertSaneHandle(handle);
            ordered_json& base = toModifiableOrderedJson(handle);
            base = parse(source);
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    // ====================================================================== //
    // Parsing & Validation

    const IJsonService::JsonHandle parseValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag tag,
        const char* const json,
        const IJsonService::JsonTag validationSchemaTag
    )
    {
        try
        {
            return toJsonHandle(
                       validatePatchAndAdd(
                           tag,
                           parse(json),
                           get(validationSchemaTag)
                       )
                   );
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    const IJsonService::JsonHandle readValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag tag,
        const char* const file,
        const IJsonService::JsonTag validationSchemaTag
    )
    {
        try
        {
            return toJsonHandle(
                       readValidateByTagPatchAndAdd(
                           tag,
                           file,
                           validationSchemaTag
                       )
                   );
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_JSON_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

}
