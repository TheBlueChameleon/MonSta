#include <base/errors.hpp>

#include "stat.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    Stat getStatFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == STAT_HP )      { return Stat::HP;       }
        else if (name == STAT_ATK)      { return Stat::ATK;      }
        else if (name == STAT_DEF)      { return Stat::DEF;      }
        else if (name == STAT_SPC)      { return Stat::SPC;      }
        else if (name == STAT_SPD)      { return Stat::SPD;      }
        else { throw  IllegalArgumentError("Unknown Stat: '"s + name.data() + "'");}
        // *INDENT-ON*
    }

    std::string_view getStatName(const Stat stat)
    {
        switch (stat)
        {
            case Stat::HP:
                return STAT_HP;
            case Stat::ATK:
                return STAT_ATK;
            case Stat::DEF:
                return STAT_DEF;
            case Stat::SPC:
                return STAT_SPC;
            case Stat::SPD:
                return STAT_SPD;
        }
        throw  IllegalArgumentError(
            "Unknown Stat ID: "s + std::to_string(static_cast<int>(stat))
        );
    }
}
