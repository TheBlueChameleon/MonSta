#include <string>

#include "base/errors.hpp"

#include "schemavalidationconstants.hpp"

#include "pokemonstatus.hpp"

using namespace SchemaValidation;
using namespace std::string_literals;

namespace SimulationMode
{

    PokemonStatus getStatusFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == POKEMON_STATUS_NORMAL   ) {return SimulationMode::PokemonStatus::NORMAL;}
        else if (name == POKEMON_STATUS_PARALYZED) {return SimulationMode::PokemonStatus::PARALYZED;}
        else if (name == POKEMON_STATUS_POISONED ) {return SimulationMode::PokemonStatus::POISONED;}
        else if (name == POKEMON_STATUS_ASLEEP   ) {return SimulationMode::PokemonStatus::ASLEEP;}
        else if (name == POKEMON_STATUS_BURNT    ) {return SimulationMode::PokemonStatus::BURNT;}
        else if (name == POKEMON_STATUS_FROZEN   ) {return SimulationMode::PokemonStatus::FROZEN;}
        else if (name == POKEMON_STATUS_FAINTED  ) {return SimulationMode::PokemonStatus::FAINTED;}
        // *INDENT-ON*

        throw EngineError("Unknown Status name: "s + name.data());
    }

    std::string_view getPokemonStatusName(const PokemonStatus status)
    {
        switch (status)
        {
            case SimulationMode::PokemonStatus::NORMAL:
                return POKEMON_STATUS_NORMAL;
            case SimulationMode::PokemonStatus::PARALYZED:
                return POKEMON_STATUS_PARALYZED;
            case SimulationMode::PokemonStatus::POISONED:
                return POKEMON_STATUS_POISONED;
            case SimulationMode::PokemonStatus::ASLEEP:
                return POKEMON_STATUS_ASLEEP;
            case SimulationMode::PokemonStatus::BURNT:
                return POKEMON_STATUS_BURNT;
            case SimulationMode::PokemonStatus::FROZEN:
                return POKEMON_STATUS_FROZEN;
            case SimulationMode::PokemonStatus::FAINTED:
                return POKEMON_STATUS_FAINTED;
        }

        throw EngineError("Unknown Status ID: "s + std::to_string(static_cast<int>(status)));
    }

} // namespace SimulationMode
