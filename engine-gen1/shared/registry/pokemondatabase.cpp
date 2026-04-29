#include <base/errors.hpp>

#include "pokemondatabase.hpp"

using namespace std::string_literals;
using namespace MetaDefinition;

namespace Registry
{
    void PokemonDatabase::addSpecies(const std::string& species, const PokemonDatabaseEntry& entry)
    {
        database.try_emplace(species, entry);
    }

    const PokemonDatabaseEntry& PokemonDatabase::getEntry(const std::string_view species)
    {
        const auto it = database.find(species.data());
        if (it == database.end())
        {
            throw IllegalArgumentError(
                "Unknown Species Name: "s + species.data()
            );
        }
        else
        {
            return it->second;
        }
    }
}
