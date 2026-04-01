#include <nlohmann/json.hpp>

#include <IJsonService.hpp>

#include "jsonservice.hpp"

namespace JsonService
{
    static JsonServiceDatabase database;

    static IJsonService::Handle toHandle(const nlohmann::json& reference)
    {
        return IJsonService::Handle(
                   reinterpret_cast<decltype(IJsonService::Handle::data)>(&reference)
               );
    }

    IJsonService exportService()
    {
        return IJsonService();
    }

    JsonServiceDatabase& getDatabase()
    {
        return database;
    }

    std::optional<JsonServiceDatabase::EntryState> getState(const std::string_view tag)
    {
        return database.getState(tag);
    }

    const nlohmann::ordered_json& get(const std::string_view tag)
    {
        return database.get(tag);
    }

    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json& json)
    {
        return database.add(tag, json);
    }

    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json&& json)
    {
        return database.add(tag, std::move(json));
    }

    const nlohmann::ordered_json& getOrAdd(const std::string_view tag, std::function<nlohmann::ordered_json()> creator)
    {
        return database.getOrAdd(tag, creator);
    }

    std::optional<std::reference_wrapper<nlohmann::ordered_json> > declare(const std::string_view tag)
    {
        return database.declare(tag);
    }

    const nlohmann::ordered_json& commit(const std::string& tag)
    {
        return database.commit(tag);
    }

}
