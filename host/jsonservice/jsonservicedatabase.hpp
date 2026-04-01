#ifndef JSONSERVICEDATABASE_HPP
#define JSONSERVICEDATABASE_HPP

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

#include <IJsonService.hpp>

namespace JsonService
{
    class JsonServiceDatabase
    {
        public:
            enum class EntryState {DECLARED, READY};
            struct Entry
            {
                mutable std::mutex mtx;
                mutable std::condition_variable cv;
                EntryState state;
                std::unique_ptr<nlohmann::json> data;
            };

        protected:
            static JsonServiceDatabase instance;

            std::mutex mutable mutex;
            std::map<std::string, Entry> database;

        protected:
            JsonServiceDatabase() = default;

        public:
            static JsonServiceDatabase& getInstance();

            std::optional<EntryState> getState(const std::string_view tag) const;

            const nlohmann::json& get(const std::string_view tag) const;

            const nlohmann::json& add(const std::string_view tag, const nlohmann::json& json);

            const nlohmann::json& add(const std::string_view tag, const nlohmann::json&& json);

            const nlohmann::json& getOrAdd(const std::string_view tag, std::function<nlohmann::json()> creator);

            std::optional<std::reference_wrapper<nlohmann::json>> declare(const std::string_view tag);

            const nlohmann::json& commit(const std::string& tag);
    };

} // namespace JsonService

#endif // JSONSERVICEDATABASE_HPP
