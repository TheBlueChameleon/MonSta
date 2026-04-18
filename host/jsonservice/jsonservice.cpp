#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <services/IJsonService.hpp>

#include "errorservice/errors.hpp"

#include "fileservice/fileservice.hpp"

#include "jsonservice.hpp"
#include "jsonservice_database_dlx.hpp"
#include "jsonservice_itemaccess_dlx.hpp"
#include "jsonservice_schemabuilder_dlx.hpp"

using namespace nlohmann;
using namespace nlohmann::json_schema;

namespace JsonService
{
    // ====================================================================== //
    // State

    static JsonServiceDatabase database;
    static bool allowComments = true;
    static bool allowExceptions = true;

    // ====================================================================== //
    // Export

    const IJsonService exportService()
    {
        return IJsonService
        {
            IJsonService_Database{
                getState_dlx,
                get_dlx,
                getOrAdd_dlx,
                getOrParse_dlx,
                declare_dlx,
                commit_dlx,

                parseValidatePatchAndAdd_dlx,
                readValidatePatchAndAdd_dlx
            },

            IJsonService_ItemAccess{
                navigateTo_dlx,
                navigateToModifiable_dlx,
                contains_dlx,

                getType_dlx,
                isNull_dlx,
                isBoolean_dlx,
                isInteger_dlx,
                isUnsigned_dlx,
                isFloat_dlx,
                isString_dlx,
                isArray_dlx,
                isObject_dlx,

                getAsBool_dlx,
                getAsInteger_dlx,
                getAsUnsigned_dlx,
                getAsFloat_dlx,
                getAsString_dlx,

                getArraySize_dlx,
                getArrayItem_dlx,

                setToNull_dlx,
                setToBool_dlx,
                setToInteger_dlx,
                setToUnsigned_dlx,
                setToFloat_dlx,
                setToString_dlx,
                setToHandle_dlx,
                setToArray_dlx,
                setToObject_dlx,
                setToParseable_dlx,

                dump_dlx
            },

            IJsonService_SchemaBuilder{
                instantiateSchemaBuilder_dlx,
                instantiateSchemaElementBuilder_dlx,
                freeSchemaBuilder_dlx,
                freeSchemaElementBuilder_dlx,

                sb_setAdditionalProperties_dlx,
                sb_addRequired_dlx,
                sb_addAllOfRequirement_dlx,
                sb_addAnyOfRequirement_dlx,
                sb_addOneOfRequirement_dlx,
                sb_addNoneOfRequirement_dlx,
                sb_addElementByName_dlx,
                sb_addElementByParseable_dlx,
                sb_addReferenceByName_dlx,
                sb_addReferenceByType_dlx,
                sb_addSubSchemaByName_dlx,
                sb_addSubSchemaByType_dlx,
                sb_addPropertyByName_dlx,
                sb_addPropertyByNameWithType_dlx,
                sb_buildAndAdd_dlx,

                seb_getName_dlx,
                seb_getJson_dlx,
                seb_setJsonByHandle_dlx,
                seb_setJsonByParseable_dlx,
                seb_setProperty_dlx,
                seb_setType_dlx,
                seb_setEnum_dlx,
                seb_setTypedArray_dlx,
                seb_setEnumArray_dlx,
                seb_setDefault_dlx,
                seb_setMinimum_dlx,
                seb_setMaximum_dlx,
                seb_setDescription_dlx,
                seb_setTitle_dlx,
                seb_setReference_dlx
            }
        };
    }

    // ====================================================================== //
    // JsonDatabase

    JsonServiceDatabase& getDatabase()
    {
        return database;
    }

    const IJsonServiceTypes::EntryState getState(const IJsonServiceTypes::JsonTag tag)
    {
        const auto opt = database.getState(tag);
        if (opt.has_value())
        {
            switch (opt.value())
            {
                case JsonServiceDatabase::EntryState::DECLARED:
                    return IJsonServiceTypes::EntryState::DECLARED;
                case JsonServiceDatabase::EntryState::READY:
                    return IJsonServiceTypes::EntryState::READY;
            }
        }
        else
        {
            return IJsonServiceTypes::EntryState::NONEXISTENT;
        }

        throw IllegalHostStateException("Unknown Entry State in tag '"s + tag.name + "'");
    }

    const nlohmann::ordered_json& get(const IJsonServiceTypes::JsonTag tag)
    {
        return database.get(tag);
    }

    const nlohmann::ordered_json& add(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json& json)
    {
        return database.add(tag, json);
    }

    const nlohmann::ordered_json& add(const IJsonServiceTypes::JsonTag tag, ordered_json&& json)
    {
        return database.add(tag, std::move(json));
    }

    const nlohmann::ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, std::function<void(nlohmann::ordered_json&)> creator)
    {
        return database.getOrAdd(tag, creator);
    }

    const ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json& json)
    {
        return database.getOrAdd(tag, json);
    }

    const ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, nlohmann::ordered_json&& json)
    {
        return database.getOrAdd(tag, std::move(json));
    }

    std::optional<std::reference_wrapper<nlohmann::ordered_json>> declare(const IJsonServiceTypes::JsonTag tag)
    {
        return database.declare(tag);
    }

    const nlohmann::ordered_json& commit(const IJsonServiceTypes::JsonTag tag)
    {
        return database.commit(tag);
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

    const ordered_json& parseAndAdd(const IJsonServiceTypes::JsonTag tag, const std::string_view data)
    {
        return getOrAdd(tag, parse(data));
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
        const IJsonServiceTypes::JsonTag tag,
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema
    )
    {
        const auto validatedData = validateAndPatch(data, schema, tag.name);
        return getOrAdd(tag, validatedData);
    }

    ordered_json read(const std::filesystem::path& file)
    {
        try
        {
            std::ifstream hFile(FileService::getInputBasePath() / file);
            return ordered_json::parse(hFile, nullptr, allowExceptions, allowComments);
        }
        catch (const nlohmann::ordered_json::exception& err)
        {
            throw JsonError(
                "Error parsing JSON file '"s + file.c_str() + "'\n" +
                err.what()
            );
        }
    }

    const ordered_json readAndAdd(const IJsonServiceTypes::JsonTag tag, const std::filesystem::path& file)
    {
        return getOrAdd(tag, read(file));
    }

    ordered_json readValidateAndPatch(const std::filesystem::path& file, const nlohmann::ordered_json& schema)
    {
        ordered_json rawJson = read(file);
        return validateAndPatch(rawJson, schema, file.c_str());
    }

    ordered_json readValidateByTagAndPatch(const std::filesystem::path& file, const IJsonServiceTypes::JsonTag validationSchemaTag)
    {
        return readValidateAndPatch(file, get(validationSchemaTag));
    }

    const ordered_json& readValidateByTagPatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::filesystem::path& file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        const auto validatedJson = readValidateByTagAndPatch(file, validationSchemaTag);
        return getOrAdd(tag, validatedJson);
    }

}
