#include <cstring>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
using namespace nlohmann;
#include <nlohmann/json-schema.hpp>
using namespace nlohmann::json_schema;

#include <services/IJsonService.hpp>

#include "errorservice/catchmacros.hpp"
#include "errorservice/errors.hpp"
#include "errorservice/errorservice.hpp"

#include "jsonservice.hpp"


// ========================================================================== //
// Code Proper

namespace JsonService
{
    // ====================================================================== //
    // State

    static JsonServiceDatabase database;
    static bool allowComments = true;
    static bool allowExceptions = true;

    // ====================================================================== //
    // Internal

    static IJsonService::JsonHandle toHandle(const nlohmann::ordered_json& reference)
    {
        return IJsonService::JsonHandle
        {
            reinterpret_cast<decltype(IJsonService::JsonHandle::data)>(&reference)
        };
    }

    static IJsonService::ModifiableJsonHandle toModifiableHandle(const nlohmann::ordered_json& reference)
    {
        return IJsonService::ModifiableJsonHandle
        {
            reinterpret_cast<decltype(IJsonService::ModifiableJsonHandle::data)>(&reference)
        };
    }

    static const ordered_json& toOrderedJson(const IJsonService::JsonHandle handle)
    {
        return *reinterpret_cast<const ordered_json*>(handle.data);
    }

    static ordered_json& toModifiableOrderedJson(const IJsonService::ModifiableJsonHandle handle)
    {
        return *reinterpret_cast<ordered_json*>(
                   const_cast<void*>(handle.data)
               );
    }

    static void assertSaneHandle(const IJsonService::JsonHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null Json Handle");
        }
    }

    static void assertSaneTag(const IJsonService::JsonTag tag)
    {
        if (tag.name == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null Json Tag");
        }

        if (std::strlen(tag.name) == 0)
        {
            throw ClientRequestError("Client attempted operation on empty Json Tag");
        }
    }

    static void assertSaneJsonPointer(const char* const jsonPointer)
    {
        if (jsonPointer == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null Json Pointer");
        }

        if (std::strlen(jsonPointer) == 0)
        {
            throw ClientRequestError("Client attempted operation on empty Json Pointer");
        }
    }

    // ====================================================================== //
    // Export

    IJsonService exportService()
    {
        return IJsonService
        {
            getState_dlx,
            get_dlx,
            add_dlx,
            getOrAdd_dlx,
            declare_dlx,
            commit_dlx,

            navigateTo_dlx,
            contains_dlx,

            isString_dlx,
            getAsString_dlx
        };
    }

    // ====================================================================== //
    // JsonDatabase

    JsonServiceDatabase& getDatabase()
    {
        return database;
    }

    const IJsonService::EntryState getState(const IJsonService::JsonTag tag)
    {
        const auto opt = database.getState(tag);
        if (opt.has_value())
        {
            switch (opt.value())
            {
                case JsonServiceDatabase::EntryState::DECLARED:
                    return IJsonService::EntryState::DECLARED;
                case JsonServiceDatabase::EntryState::READY:
                    return IJsonService::EntryState::READY;
            }
        }
        else
        {
            return IJsonService::EntryState::NONEXISTENT;
        }

        throw IllegalHostStateException("Unknown Entry State in tag '"s + tag.name + "'");
    }

    const nlohmann::ordered_json& get(const IJsonService::JsonTag tag)
    {
        return database.get(tag.name);
    }

    const nlohmann::ordered_json& add(const IJsonService::JsonTag tag, const nlohmann::ordered_json& json)
    {
        return database.add(tag, json);
    }

    const nlohmann::ordered_json& add(const IJsonService::JsonTag tag, const nlohmann::ordered_json&& json)
    {
        return database.add(tag, std::move(json));
    }

    const nlohmann::ordered_json& getOrAdd(const IJsonService::JsonTag tag, std::function<void(nlohmann::ordered_json&)> creator)
    {
        return database.getOrAdd(tag, creator);
    }

    std::optional<std::reference_wrapper<nlohmann::ordered_json> > declare(const IJsonService::JsonTag tag)
    {
        return database.declare(tag);
    }

    const nlohmann::ordered_json& commit(const IJsonService::JsonTag tag)
    {
        return database.commit(tag);
    }

    // ---------------------------------------------------------------------- //
    // DyLib export

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
            return toHandle(get(tag));
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    const IJsonService::JsonHandle add_dlx(const IJsonService::JsonTag tag, const IJsonService::JsonHandle handle)
    {
        try
        {
            assertSaneTag(tag);
            assertSaneHandle(handle);
            return toHandle(
                       add(tag, toOrderedJson(handle))
                   );
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
                creator(toModifiableHandle(json));
            };

            return toHandle(getOrAdd(tag, convertedCreator));
        }
        CATCH_ABSTRACT_ERROR(IJsonService::JsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::JsonHandle(nullptr))
    }

    const IJsonService::ModifiableJsonHandle declare_dlx(const IJsonService::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return toModifiableHandle(declare(tag));
        }
        CATCH_ABSTRACT_ERROR(IJsonService::ModifiableJsonHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonService::ModifiableJsonHandle(nullptr))
    }

    const IJsonService::JsonHandle commit_dlx(const IJsonService::JsonTag tag)
    {
        try
        {
            assertSaneTag(tag);
            return toHandle(database.commit(tag));
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
                return toHandle(target);
            }
            else
            {
                const auto& target = base.at(jsonPointer);
                return toHandle(target);
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

            return toHandle(base.at(index));
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

    void setAllowComments(bool value)
    {
        allowComments = value;
    }

    void setAllowExceptions(bool value)
    {
        allowExceptions = value;
    }

    nlohmann::ordered_json parse(const std::string_view data)
    {
        try
        {
            return ordered_json::parse(data, nullptr, allowExceptions, allowComments);
        }
        catch (const nlohmann::ordered_json::exception& e)
        {
            throw JsonError(e.what());
        }
    }

    const ordered_json& parseAndAdd(const IJsonService::JsonTag tag, const std::string_view data)
    {
        return add(tag, parse(data));
    }

    json validate(
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema,
        const std::string_view origin
    )
    {
        json_validator validator;
        try
        {
            validator.set_root_schema(schema);
        }
        catch (const std::invalid_argument& e)
        {
            throw JsonError(
                "Invalid state of simulation schema:\n"s +
                e.what()
            );
        }

        try
        {
            return validator.validate(data);
        }
        catch (const std::invalid_argument& e)
        {
            throw JsonError(
                "JSON data from '"s + origin.data() + "' are invalid:\n" +
                e.what()
            );
        }
    }

    ordered_json validateAndPatch(
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema,
        const std::string_view origin
    )
    {
        try
        {
            const auto patch = validate(data, schema, origin);
            return data.patch(patch);
        }
        catch (const nlohmann::ordered_json::exception& e)
        {
            throw JsonError(e.what());
        }
    }

    const ordered_json& validatePatchAndAdd(
        const IJsonService::JsonTag tag,
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema
    )
    {
        const auto validatedData = validateAndPatch(data, schema, tag.name);
        return add(tag, validatedData);
    }

    ordered_json read(const std::filesystem::path& file)
    {
        try
        {
            std::ifstream hFile(file);
            auto data = ordered_json::parse(hFile, nullptr, allowExceptions, allowComments);
            return data;
        }
        catch (const nlohmann::ordered_json::exception& err)
        {
            throw JsonError(
                "Error parsing JSON file '"s + file.c_str() + "'\n" +
                err.what()
            );
        }
    }

    const ordered_json readAndAdd(const IJsonService::JsonTag tag, const std::filesystem::path& file)
    {
        return add(tag, read(file));
    }

    ordered_json readValidateAndPatch(const std::filesystem::path& file, const nlohmann::ordered_json& schema)
    {
        ordered_json rawJson = read(file);
        return validateAndPatch(rawJson, schema, file.c_str());
    }

    ordered_json readValidateByTagAndPatch(const std::filesystem::path& file, const IJsonService::JsonTag validationSchemaTag)
    {
        return readValidateAndPatch(file, get(validationSchemaTag));
    }

    const ordered_json& readValidateByTagPatchAndAdd(
        const IJsonService::JsonTag tag,
        const std::filesystem::path& file,
        const IJsonService::JsonTag validationSchemaTag
    )
    {
        const auto validatedJson = readValidateByTagAndPatch(file, validationSchemaTag);
        return add(tag, validatedJson);
    }

    const IJsonService::JsonHandle validatePatchAndAdd_dlx(
        const IJsonService::JsonTag tag,
        const IJsonService::JsonHandle& data,
        const IJsonService::JsonTag validationSchemaTag
    )
    {
        try
        {
            return toHandle(
                       validatePatchAndAdd(
                           tag,
                           toOrderedJson(data),
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
            return toHandle(
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
