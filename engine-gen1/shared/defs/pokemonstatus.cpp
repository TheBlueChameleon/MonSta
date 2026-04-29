#include <string>

#include "base/errors.hpp"

#include "shared/schemavalidationconstants.hpp"

#include "pokemonstatus.hpp"

using namespace SchemaValidation;
using namespace std::string_literals;

namespace MetaDefinition
{
    PokemonStatus getPokemonStatusFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == POKEMON_STATUS_NORMAL   ) {return MetaDefinition::PokemonStatus::NORMAL;}
        else if (name == POKEMON_STATUS_PARALYZED) {return MetaDefinition::PokemonStatus::PARALYZED;}
        else if (name == POKEMON_STATUS_POISONED ) {return MetaDefinition::PokemonStatus::POISONED;}
        else if (name == POKEMON_STATUS_ASLEEP   ) {return MetaDefinition::PokemonStatus::ASLEEP;}
        else if (name == POKEMON_STATUS_BURNT    ) {return MetaDefinition::PokemonStatus::BURNT;}
        else if (name == POKEMON_STATUS_FROZEN   ) {return MetaDefinition::PokemonStatus::FROZEN;}
        else if (name == POKEMON_STATUS_FAINTED  ) {return MetaDefinition::PokemonStatus::FAINTED;}
        // *INDENT-ON*

        throw IllegalArgumentError("Unknown Status name: "s + name.data());
    }

    std::string_view getPokemonStatusName(const PokemonStatus status)
    {
        switch (status)
        {
            case MetaDefinition::PokemonStatus::NORMAL:
                return POKEMON_STATUS_NORMAL;
            case MetaDefinition::PokemonStatus::PARALYZED:
                return POKEMON_STATUS_PARALYZED;
            case MetaDefinition::PokemonStatus::POISONED:
                return POKEMON_STATUS_POISONED;
            case MetaDefinition::PokemonStatus::ASLEEP:
                return POKEMON_STATUS_ASLEEP;
            case MetaDefinition::PokemonStatus::BURNT:
                return POKEMON_STATUS_BURNT;
            case MetaDefinition::PokemonStatus::FROZEN:
                return POKEMON_STATUS_FROZEN;
            case MetaDefinition::PokemonStatus::FAINTED:
                return POKEMON_STATUS_FAINTED;
        }

        throw IllegalArgumentError("Unknown Status ID: "s + std::to_string(static_cast<int>(status)));
    }

} // namespace SimulationMode
