#ifndef JSONSERVICEDATABASE_HPP
#define JSONSERVICEDATABASE_HPP

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <string_view>

#include <nlohmann/json_fwd.hpp>

#include <services/IJsonService.hpp>

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
                std::unique_ptr<nlohmann::ordered_json> data;
            };

        private:
            std::mutex mutable mutex;
            std::map<std::string, Entry> database;

        public:
            JsonServiceDatabase() = default;
            static JsonServiceDatabase& getInstance();

            std::optional<EntryState> getState(const IJsonServiceTypes::JsonTag tag) const;

            const nlohmann::ordered_json& get(const IJsonServiceTypes::JsonTag tag) const;

            const nlohmann::ordered_json& add(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json& json);

            const nlohmann::ordered_json& add(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json&& json);

            const nlohmann::ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, std::function<void (nlohmann::ordered_json&)> creator);

            const nlohmann::ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json& json);

            const nlohmann::ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, nlohmann::ordered_json&& json);

            std::optional<std::reference_wrapper<nlohmann::ordered_json>> declare(const IJsonServiceTypes::JsonTag tag);

            const nlohmann::ordered_json& commit(const IJsonServiceTypes::JsonTag tag);
    };
} // namespace JsonService

#endif // JSONSERVICEDATABASE_HPP
