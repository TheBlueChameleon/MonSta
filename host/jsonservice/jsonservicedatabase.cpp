#include <string>
using namespace std::string_literals;

#include "errors.hpp"

#include "jsonservicedatabase.hpp"

namespace JsonService
{
    std::optional<JsonServiceDatabase::EntryState> JsonServiceDatabase::getState(const IJsonService::JsonTag tag) const
    {
        std::lock_guard lock(mutex);

        auto it = database.find(tag.name);
        if (it == database.end())
        {
            return std::nullopt;
        }

        return it->second.state;
    }

    static void waitForCompletion(const JsonServiceDatabase::Entry& entry)
    {
        std::unique_lock lock(entry.mtx);
        entry.cv.wait(lock, [&entry] { return entry.state == JsonServiceDatabase::EntryState::READY; });
    }

    const nlohmann::ordered_json& JsonServiceDatabase::get(const IJsonService::JsonTag tag) const
    {
        const Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto it = database.find(tag.name);
            if (it == database.end())
            {
                throw LookupError("Unknown JSON tag: '"s + tag.name + "'");
            }

            entry = &it->second;
        }

        waitForCompletion(*entry);

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::add(
        const IJsonService::JsonTag tag,
        const nlohmann::ordered_json& json
    )
    {
        Entry* entry;

        // TODO: extract shared code with add(move)
        {
            std::lock_guard lock(mutex);

            auto [it, inserted] = database.try_emplace(tag.name);

            if (!inserted)
            {
                throw LookupError("JSON Tag already exists: '"s + tag.name + "'");
            }

            entry = &it->second;
        }

        {
            std::lock_guard entryLock(entry->mtx);

            entry->data = std::make_unique<nlohmann::ordered_json>(json); // copy
            entry->state = EntryState::READY;
        }

        entry->cv.notify_all();

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::add(const IJsonService::JsonTag tag, const nlohmann::ordered_json&& json)
    {
        Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto [it, inserted] = database.try_emplace(tag.name);

            if (!inserted)
            {
                throw LookupError("JSON Tag already exists: '"s + tag.name + "'");
            }

            entry = &it->second;
        }

        {
            std::lock_guard entryLock(entry->mtx);

            entry->data = std::make_unique<nlohmann::ordered_json>(std::move(json));
            entry->state = EntryState::READY;
        }

        entry->cv.notify_all();

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::getOrAdd(
        const IJsonService::JsonTag tag,
        std::function<void (nlohmann::ordered_json&)> creator
    )
    {
        Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto [it, inserted] = database.try_emplace(tag.name);
            entry = &it->second;

            if (inserted)
            {
                std::lock_guard entryLock(entry->mtx);
                entry->state = EntryState::DECLARED;
            }
        }

        {
            std::unique_lock entryLock(entry->mtx);

            if (entry->state == EntryState::READY)
            {
                return *entry->data;
            }

            if (entry->state == EntryState::DECLARED && !entry->data)
            {
                // This thread initializes
                nlohmann::ordered_json createdJson;
                creator(createdJson);
                entry->data = std::make_unique<nlohmann::ordered_json>(std::move(createdJson));
                entry->state = EntryState::READY;

                entryLock.unlock();
                entry->cv.notify_all();

                return *entry->data;
            }

            // Otherwise: wait for someone else
            entry->cv.wait(entryLock, [&entry]
            {
                return entry->state == EntryState::READY;
            });

            return *entry->data;
        }
    }

    std::optional<std::reference_wrapper<nlohmann::ordered_json>> JsonServiceDatabase::declare(const IJsonService::JsonTag tag)
    {
        Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto [it, inserted] = database.try_emplace(tag.name);

            if (!inserted)
            {
                if (it->second.state != EntryState::DECLARED)
                {
                    throw LookupError("JSON Tag already exists: '"s + tag.name + "'");
                }

                return std::nullopt;
            }

            entry = &it->second;
        }

        {
            std::lock_guard entryLock(entry->mtx);

            entry->data = std::make_unique<nlohmann::ordered_json>();
            entry->state = EntryState::DECLARED;
        }

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::commit(const IJsonService::JsonTag tag)
    {
        Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto it = database.find(tag.name);
            if (it == database.end())
            {
                throw LookupError("Unknown JSON tag: '"s + tag.name + "'");
            }

            entry = &it->second;
        }

        {
            std::lock_guard entryLock(entry->mtx);
            if (entry->state != EntryState::DECLARED)
            {
                throw LookupError("Unknown JSON tag: '"s + tag.name + "' has already been committed!");
            }

            if (!entry->data)
            {
                throw IllegalStateException("Commit on uninitialized JSON");
            }


            entry->state = EntryState::READY;
        }

        entry->cv.notify_all();

        return *entry->data;
    }


} // namespace JsonService
