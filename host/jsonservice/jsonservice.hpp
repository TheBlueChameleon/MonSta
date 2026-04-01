#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <IJsonService.hpp>

#include "jsonschemabuilder.hpp"
#include "jsonservicedatabase.hpp"

namespace JsonService
{
    IJsonService exportService();

    // ---------------------------------------------------------------------- //
    // JsonDatabase

    enum class EntryState {NONEXISTENT, DECLARED, READY};

    JsonServiceDatabase& getDatabase();

    std::optional<JsonServiceDatabase::EntryState> getState(const std::string_view tag);
    const nlohmann::ordered_json& get(const std::string_view tag);
    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json& json);
    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json&& json);
    const nlohmann::ordered_json& getOrAdd(const std::string_view tag, std::function<nlohmann::ordered_json()> creator);
    std::optional<std::reference_wrapper<nlohmann::ordered_json>> declare(const std::string_view tag);
    const nlohmann::ordered_json& commit(const std::string& tag);

    // ---------------------------------------------------------------------- //
    // Parsing


    // ---------------------------------------------------------------------- //
    // Validation


    // ---------------------------------------------------------------------- //
    // Schema Builder Operations




    /* setAllowComments(bool)
     * setAllowExceptions(bool)
     *
     * parse(string) -> json
     * public parseAndRegister(tag, string)
     * read(file)    -> json
     * public readAndRegister(tag, file)
     * validate(json, json) -> json
     * validate(json, tag)  -> json
     * patch(json, json) -> json
     * merge_patch(json, json)?  -> json
     *
     * readValidateAndPatch(file, json)
     * parseValidateAndPatch(file, json)
     * public readValidateAndPatch(file, tag)
     * public parseValidateAndPatch(file, tag)
     *
     * json ops:
     * getHandle(tag) -> Handle
     * getHandleFromPath(tag, path) -> Handle
     * getElement(Handle, item) -> Handle
     * emplace(Handle, path, *) -> Handle
     * asString(Handle), ...
     *
     * json schema builder ops:
     * ???
     */
}

#endif // JSONSERVICE_HPP
