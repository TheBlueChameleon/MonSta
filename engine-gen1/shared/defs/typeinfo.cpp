#include <base/errors.hpp>

#include "typeinfo.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    MoveCategory getMoveCategoryFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == PHYSICAL) {return MoveCategory::PHYSICAL;}
        else if (name == SPECIAL ) {return MoveCategory::SPECIAL ;}
        else if (name == STATUS  ) {return MoveCategory::STATUS  ;}
        // *INDENT-ON*

        throw IllegalArgumentError("Unknown move category: "s + name.data());
    }

    std::string_view getMoveCategoryName(const MoveCategory category)
    {
        switch (category)
        {
            case MoveCategory::PHYSICAL:
                return PHYSICAL;
            case MoveCategory::SPECIAL:
                return SPECIAL;
            case MoveCategory::STATUS:
                return STATUS;
        }

        throw IllegalArgumentError("Unknown move category id: "s + std::to_string(static_cast<int>(category)));
    }

} // namespace SimulationMode
