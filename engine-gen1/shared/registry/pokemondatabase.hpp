#ifndef POKEMONDATABASE_HPP
#define POKEMONDATABASE_HPP

#include <string>
#include <unordered_map>

#include "shared/defs/pokemondatabaseentry.hpp"

namespace SimulationMode
{
    class PokemonDatabase
    {
        public:
            static constexpr auto SPECIES   = "Species";
            static constexpr auto HP        = "HP";
            static constexpr auto ATK       = "ATK";
            static constexpr auto DEF       = "DEF";
            static constexpr auto SPD       = "SPD";
            static constexpr auto SPC       = "SPC";
            static constexpr auto TYPE1     = "Type1";
            static constexpr auto TYPE2     = "Type2";
            static constexpr auto EXPYIELD  = "ExpYield";
            static constexpr auto EXPGROUP  = "ExpGroup";

        private:
            std::unordered_map<std::string, PokemonDatabaseEntry> database;

        public:
            PokemonDatabase() = default;

            void addSpecies(const std::string& species, const PokemonDatabaseEntry& entry);

            const PokemonDatabaseEntry& getEntry(const std::string_view species);
    };
}

#endif // POKEMONDATABASE_HPP
