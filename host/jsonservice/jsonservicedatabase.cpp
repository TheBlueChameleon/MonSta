#include <string>
using namespace std::string_literals;

#include "errors.hpp"

#include "jsonservicedatabase.hpp"

namespace JsonService
{
    JsonServiceDatabase JsonServiceDatabase::instance;

    JsonServiceDatabase& JsonServiceDatabase::getInstance()
    {
        return instance;
    }

    IJsonService::Handle JsonServiceDatabase::toHandle(const std::unique_ptr<nlohmann::json>& reference)
    {
        return IJsonService::Handle{reference.get()};
    }

    static void waitForCompletion(const JsonServiceDatabase::Entry& lookup)
    {
        std::unique_lock lock(lookup.mtx);
        lookup.cv.wait(lock, [&lookup] { return lookup.state == JsonServiceDatabase::EntryState::READY; });
    }

    const nlohmann::json& JsonServiceDatabase::get(const std::string& tag) const
    {
        const Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto it = database.find(tag);
            if (it == database.end())
            {
                throw LookupError("Unknown JSON tag: '"s + tag + "'");
            }

            entry = &it->second;
        }

        waitForCompletion(*entry);

        return *entry->data;
    }

    const nlohmann::json& JsonServiceDatabase::add(const std::string& tag, const nlohmann::json& json)
    {
        Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto [it, inserted] = database.try_emplace(tag);

            if (!inserted)
            {
                throw std::runtime_error("JSON Tag already exists: '"s + tag + "'");
            }

            entry = &it->second;
        }

        {
            std::lock_guard entryLock(entry->mtx);

            entry->data = std::make_unique<nlohmann::json>(json); // copy
            entry->state = EntryState::READY;
        }

        entry->cv.notify_all();

        return *entry->data;
    }

    const nlohmann::json& JsonServiceDatabase::getOrAdd(
        const std::string& tag,
        std::function<nlohmann::json()> creator
    )
    {
        Entry* entry;

        {
            std::lock_guard lock(mutex);

            auto [it, inserted] = database.try_emplace(tag);
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
                entry->data = std::make_unique<nlohmann::json>(creator());
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


} // namespace JsonService
