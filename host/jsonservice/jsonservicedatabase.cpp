#include <string>
using namespace std::string_literals;

#include "errorservice/errors.hpp"

#include "jsonservicedatabase.hpp"

// TODO: de-duplicate some of the code

namespace JsonService
{
    static const JsonServiceDatabase::Entry* findEntry(
        const std::map<std::string, JsonServiceDatabase::Entry>& database,
        std::mutex& mutex,
        const IJsonServiceTypes::JsonTag tag
    )
    {
        std::lock_guard lock(mutex);

        auto it = database.find(tag.name);
        if (it == database.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    enum class EntryEmplacementVariant {Add, GetOrAdd, Declare};
    static JsonServiceDatabase::Entry* emplaceEntry(
        std::map<std::string, JsonServiceDatabase::Entry>& database,
        std::mutex& mutex,
        const IJsonServiceTypes::JsonTag tag,
        EntryEmplacementVariant variant
    )
    {
        std::lock_guard lock(mutex);

        auto [it, inserted] = database.try_emplace(tag.name);
        JsonServiceDatabase::Entry* entry = &it->second;

        switch (variant)
        {
            case JsonService::EntryEmplacementVariant::Add:
                if (!inserted)
                {
                    throw LookupError("JSON Tag already exists: '"s + tag.name + "'");
                };
                break;

            case JsonService::EntryEmplacementVariant::GetOrAdd:
                if (inserted)
                {
                    std::lock_guard entryLock(entry->mtx);
                    entry->state = JsonServiceDatabase::EntryState::DECLARED;
                };
                break;

            case JsonService::EntryEmplacementVariant::Declare:
                if (!inserted)
                {
                    if (entry->state != JsonServiceDatabase::EntryState::DECLARED)
                    {
                        throw LookupError("JSON Tag already exists: '"s + tag.name + "'");
                    }

                    return nullptr;
                }
                break;
        }

        return entry;
    }

    static void waitForCompletion(const JsonServiceDatabase::Entry& entry)
    {
        std::unique_lock lock(entry.mtx);
        entry.cv.wait(lock, [&entry] { return entry.state == JsonServiceDatabase::EntryState::READY; });
    }

    std::optional<JsonServiceDatabase::EntryState> JsonServiceDatabase::getState(const IJsonServiceTypes::JsonTag tag) const
    {
        const Entry* entry = findEntry(database, mutex, tag);
        return (entry == nullptr) ?
               std::nullopt : std::optional(entry->state);
    }

    const nlohmann::ordered_json& JsonServiceDatabase::get(const IJsonServiceTypes::JsonTag tag) const
    {
        const Entry* entry = findEntry(database, mutex, tag);
        if (entry == nullptr)
        {
            throw LookupError("Unknown JSON tag: '"s + tag.name + "'");
        }

        waitForCompletion(*entry);

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::add(
        const IJsonServiceTypes::JsonTag tag,
        const nlohmann::ordered_json& json
    )
    {
        Entry* entry = emplaceEntry(database, mutex, tag, EntryEmplacementVariant::Add);

        {
            std::lock_guard entryLock(entry->mtx);

            entry->data = std::make_unique<nlohmann::ordered_json>(json); // copy
            entry->state = EntryState::READY;
        }

        entry->cv.notify_all();

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::add(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json&& json)
    {
        Entry* entry = emplaceEntry(database, mutex, tag, EntryEmplacementVariant::Add);

        {
            std::lock_guard entryLock(entry->mtx);

            entry->data = std::make_unique<nlohmann::ordered_json>(std::move(json));
            entry->state = EntryState::READY;
        }

        entry->cv.notify_all();

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::getOrAdd(
        const IJsonServiceTypes::JsonTag tag,
        std::function<void (nlohmann::ordered_json&)> creator
    )
    {
        Entry* entry = emplaceEntry(database, mutex, tag, EntryEmplacementVariant::GetOrAdd);

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

    const nlohmann::ordered_json& JsonServiceDatabase::getOrAdd(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json& json)
    {
        Entry* entry = emplaceEntry(database, mutex, tag, EntryEmplacementVariant::GetOrAdd);

        {
            std::unique_lock entryLock(entry->mtx);

            if (entry->state == EntryState::READY)
            {
                return *entry->data;
            }

            if (entry->state == EntryState::DECLARED && !entry->data)
            {
                // This thread initializes
                entry->data = std::make_unique<nlohmann::ordered_json>(json);
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

    const nlohmann::ordered_json& JsonServiceDatabase::getOrAdd(const IJsonServiceTypes::JsonTag tag, nlohmann::ordered_json&& json)
    {
        Entry* entry = emplaceEntry(database, mutex, tag, EntryEmplacementVariant::GetOrAdd);

        {
            std::unique_lock entryLock(entry->mtx);

            if (entry->state == EntryState::READY)
            {
                return *entry->data;
            }

            if (entry->state == EntryState::DECLARED && !entry->data)
            {
                // This thread initializes
                entry->data = std::make_unique<nlohmann::ordered_json>(std::move(json));
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

    std::optional<std::reference_wrapper<nlohmann::ordered_json>> JsonServiceDatabase::declare(const IJsonServiceTypes::JsonTag tag)
    {
        Entry* entry = emplaceEntry(database, mutex, tag, EntryEmplacementVariant::Declare);
        if (entry == nullptr)
        {
            return std::nullopt;
        }

        {
            std::lock_guard entryLock(entry->mtx);

            entry->data = std::make_unique<nlohmann::ordered_json>();
            entry->state = EntryState::DECLARED;
        }

        return *entry->data;
    }

    const nlohmann::ordered_json& JsonServiceDatabase::commit(const IJsonServiceTypes::JsonTag tag)
    {
        Entry* entry = const_cast<Entry*>(findEntry(database, mutex, tag));

        {
            std::lock_guard entryLock(entry->mtx);
            if (entry->state != EntryState::DECLARED)
            {
                throw LookupError("Invalid JSON tag: '"s + tag.name + "' has already been committed!");
            }

            if (!entry->data)
            {
                throw IllegalHostStateException("Commit on uninitialized JSON");
            }


            entry->state = EntryState::READY;
        }

        entry->cv.notify_all();

        return *entry->data;
    }


} // namespace JsonService
