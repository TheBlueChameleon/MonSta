#include <string>

#include "base/errors.hpp"

#include "shared/schemavalidationconstants.hpp"

#include "statuscondition.hpp"

using namespace SchemaValidation;
using namespace std::string_literals;

namespace MetaDefinition
{
    StatusCondition getStatusConditionFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == POKEMON_STATUS_NORMAL   ) { return StatusCondition::NORMAL;    }
        else if (name == POKEMON_STATUS_PARALYZED) { return StatusCondition::PARALYZED; }
        else if (name == POKEMON_STATUS_POISONED ) { return StatusCondition::POISONED;  }
        else if (name == POKEMON_STATUS_ASLEEP   ) { return StatusCondition::ASLEEP;    }
        else if (name == POKEMON_STATUS_BURNT    ) { return StatusCondition::BURNT;     }
        else if (name == POKEMON_STATUS_FROZEN   ) { return StatusCondition::FROZEN;    }
        else if (name == POKEMON_STATUS_FAINTED  ) { return StatusCondition::FAINTED;   }
        else if (name == POKEMON_STATUS_FLINCHED ) { return StatusCondition::FLINCHED;  }
        else if (name == POKEMON_STATUS_CONFUSED ) { return StatusCondition::CONFUSED;  }
        else if (name == POKEMON_STATUS_TOXICED  ) { return StatusCondition::TOXICED;   }
        else if (name == POKEMON_STATUS_BOUND    ) { return StatusCondition::BOUND;     }
        else if (name == POKEMON_STATUS_SEEDED   ) { return StatusCondition::SEEDED;    }
        // *INDENT-ON*

        throw IllegalArgumentError("Unknown Status name: "s + name.data());
    }

    std::string_view getStatusConditionName(const StatusCondition status)
    {
        switch (status)
        {
            case StatusCondition::NORMAL:
                return POKEMON_STATUS_NORMAL;
            case StatusCondition::PARALYZED:
                return POKEMON_STATUS_PARALYZED;
            case StatusCondition::POISONED:
                return POKEMON_STATUS_POISONED;
            case StatusCondition::ASLEEP:
                return POKEMON_STATUS_ASLEEP;
            case StatusCondition::BURNT:
                return POKEMON_STATUS_BURNT;
            case StatusCondition::FROZEN:
                return POKEMON_STATUS_FROZEN;
            case StatusCondition::FAINTED:
                return POKEMON_STATUS_FAINTED;
            case MetaDefinition::StatusCondition::FLINCHED:
                return POKEMON_STATUS_FLINCHED;
            case MetaDefinition::StatusCondition::CONFUSED:
                return POKEMON_STATUS_CONFUSED;
            case MetaDefinition::StatusCondition::TOXICED:
                return POKEMON_STATUS_TOXICED;
            case MetaDefinition::StatusCondition::BOUND:
                return POKEMON_STATUS_BOUND;
            case MetaDefinition::StatusCondition::SEEDED:
                return POKEMON_STATUS_SEEDED;
        }

        throw IllegalArgumentError("Unknown Status ID: "s + std::to_string(static_cast<int>(status)));
    }

} // namespace SimulationMode
