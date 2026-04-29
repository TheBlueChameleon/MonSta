#include <base/errors.hpp>

#include "pokemondatabaseentry.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    ExperienceGroup getExperienceGroupFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == FAST       ) {return ExperienceGroup::FAST;}
        else if (name == MEDIUM_FAST) {return ExperienceGroup::MEDIUM_FAST;}
        else if (name == MEDIUM_SLOW) {return ExperienceGroup::MEDIUM_SLOW;}
        else if (name == SLOW       ) {return ExperienceGroup::SLOW;}
        // *INDENT-ON*

        throw IllegalArgumentError("Unknown Experience Group name: "s + name.data());
    }

    std::string_view getExperienceGroupName(const ExperienceGroup experienceGroup)
    {
        switch (experienceGroup)
        {
            case MetaDefinition::ExperienceGroup::FAST:
                break;
            case MetaDefinition::ExperienceGroup::MEDIUM_FAST:
                break;
            case MetaDefinition::ExperienceGroup::MEDIUM_SLOW:
                break;
            case MetaDefinition::ExperienceGroup::SLOW:
                break;
        }

        throw IllegalArgumentError("Unknown Experience Group ID: "s + std::to_string(static_cast<int>(experienceGroup)));
    }

} // namespace SimulationMode
