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

    const nlohmann::ordered_json& getOrAdd(const IJsonService::JsonTag tag, std::function<nlohmann::ordered_json()> creator)
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

    const IJsonService::JsonHandle getOrAdd_dlx(const IJsonService::JsonTag tag, const IJsonService::JsonHandle(*creator)())
    {
        assertSaneTag(tag);
        if (creator == nullptr)
        {
            throw ClientRequestError("Client attempted getOrAdd with null creator");
        }

        auto convertedCreator = [&creator]()
        {
            return toOrderedJson(creator());
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

    const char* const getAsString_dlx(const IJsonService::JsonHandle handle)
    {
        assertSaneHandle(handle);
        const ordered_json& base = toOrderedJson(handle);
        if (!base.is_string())
        {
            throw ClientRequestError("Client attempted to read Json object as String");
        }
        const auto ptr = base.get_ptr<const ordered_json::string_t*>();
        return ptr->data();
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
