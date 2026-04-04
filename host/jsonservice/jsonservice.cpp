#include <cstring>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
using namespace nlohmann;
#include <nlohmann/json-schema.hpp>
using namespace nlohmann::json_schema;

#include <IJsonService.hpp>

#include "errors.hpp"

#include "jsonservice.hpp"

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

        throw IllegalStateException("Unknown Entry State in tag '"s + tag.name + "'");
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
        assertSaneTag(tag);
        return getState(tag);
    }

    const IJsonService::JsonHandle get_dlx(const IJsonService::JsonTag tag)
    {
        assertSaneTag(tag);
        return toHandle(get(tag));
    }

    const IJsonService::JsonHandle add_dlx(const IJsonService::JsonTag tag, const IJsonService::JsonHandle handle)
    {
        assertSaneTag(tag);
        assertSaneHandle(handle);
        return toHandle(
                   add(tag, toOrderedJson(handle))
               );
    }

    const IJsonService::JsonHandle getOrAdd_dlx(
        const IJsonService::JsonTag tag,
        const void(*creator)(const IJsonService::ModifiableJsonHandle)
    )
    {
        assertSaneTag(tag);
        if (creator == nullptr)
        {
            throw ClientRequestError("Client attempted getOrAdd with null creator");
        }

        auto convertedCreator = [&creator](ordered_json& json)
        {
            creator(toModifiableHandle(json));
        };

        return toHandle(getOrAdd(tag, convertedCreator));
    }

    const IJsonService::ModifiableJsonHandle declare_dlx(const IJsonService::JsonTag tag)
    {
        assertSaneTag(tag);
        return toModifiableHandle(declare(tag));
    }

    const IJsonService::JsonHandle commit_dlx(const IJsonService::JsonTag tag)
    {
        assertSaneTag(tag);
        return toHandle(database.commit(tag));
    }

    // ====================================================================== //
    // Json compatibility layer

    const IJsonService::JsonHandle navigateTo_dlx(const IJsonService::JsonHandle handle, const char* const jsonPointer)
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

    const bool contains_dlx(const IJsonService::JsonHandle handle, const char* const elementName)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.contains(elementName);
    }

    const IJsonService::JsonType getType(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return static_cast<IJsonService::JsonType>(base.type());
    }

    const bool isNull_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_null();
    }

    const bool isBoolean_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_boolean();
    }

    const bool isInteger_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_number_integer();
    }

    const bool isUnsigned_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_number_unsigned();
    }

    const bool isFloat_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_number_float();
    }

    const bool isString_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_string();
    }

    const bool isArray_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_array();
    }

    const bool isObject_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.is_object();
    }

    const bool getAsBool_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        if (!base.is_boolean())
        {
            throw ClientRequestError("Client attempted to read non-boolean Json object as boolean");
        }
        return base.get<bool>();
    }

    const int getAsInteger_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        if (!base.is_number_integer())
        {
            throw ClientRequestError("Client attempted to read non-integer Json object as integer");
        }
        return base.get<int>();
    }

    const unsigned long long getAsUnsigned_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        if (!base.is_number_unsigned())
        {
            throw ClientRequestError("Client attempted to read non-unsigned Json object as unsigned");
        }
        return base.get<unsigned long long>();
    }

    const double getAsFloat_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        if (!base.is_number_float())
        {
            throw ClientRequestError("Client attempted to read non-float Json object as float");
        }
        return base.get<double>();
    }

    const char* const getAsString_dlx(const IJsonService::JsonHandle handle)
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

    const int getArraySize_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        return base.size();
    }

    const IJsonService::JsonHandle getArrayItem_dlx(const IJsonService::JsonHandle handle, const int index)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        if (!base.is_array())
        {
            throw ClientRequestError("Client attempted array operation on non-array Json element");
        }
        if (index < 0 ||index >= base.size())
        {
            throw ClientRequestError("Client attempted array operation with out-of-bounds index "s + std::to_string(index));
        }

        return toHandle(base.at(index));
    }

    void setToNull_dlx(const IJsonService::ModifiableJsonHandle handle)
    {
        assertSaneHandle(handle);
        ordered_json& base = toModifiableOrderedJson(handle);
        base = ordered_json();
    }

    void setToBool_dlx(const IJsonService::ModifiableJsonHandle handle, const bool value)
    {
        assertSaneHandle(handle);
        ordered_json& base = toModifiableOrderedJson(handle);
        base = value;
    }

    void setToInteger_dlx(const IJsonService::ModifiableJsonHandle handle, const int value)
    {
        assertSaneHandle(handle);
        ordered_json& base = toModifiableOrderedJson(handle);
        base = value;
    }

    void setToUnsigned_dlx(const IJsonService::ModifiableJsonHandle handle, const unsigned int value)
    {
        assertSaneHandle(handle);
        ordered_json& base = toModifiableOrderedJson(handle);
        base = value;
    }

    void setToFloat_dlx(const IJsonService::ModifiableJsonHandle handle, const double value)
    {
        assertSaneHandle(handle);
        ordered_json& base = toModifiableOrderedJson(handle);
        base = value;
    }

    void setToString_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const value)
    {
        assertSaneHandle(handle);
        ordered_json& base = toModifiableOrderedJson(handle);
        base = value;
    }

    void setToHandle_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source)
    {
        assertSaneHandle(source);
        ordered_json& base = toModifiableOrderedJson(handle);
        base = toOrderedJson(source);
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
        return ordered_json::parse(data, nullptr, allowExceptions, allowComments);
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
            throw CriticalAbort(
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
            throw CriticalAbort(
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
        const auto patch = validate(data, schema, origin);
        return data.patch(patch);
    }

    const ordered_json& validatePatchAndAdd(const IJsonService::JsonTag tag, const nlohmann::ordered_json& data, const nlohmann::ordered_json& schema)
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
        catch (const nlohmann::ordered_json::parse_error& err)
        {
            throw CriticalAbort(
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

}
