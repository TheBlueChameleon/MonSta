#include <base/errors.hpp>

#include "typeinfo.hpp"

using namespace std::string_literals;

namespace SimulationMode
{

    MoveCategory getMoveCategoryFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == PHYSICAL) {return MoveCategory::PHYSICAL;}
        else if (name == SPECIAL ) {return MoveCategory::SPECIAL ;}
        else if (name == STATUS  ) {return MoveCategory::STATUS  ;}
        // *INDENT-ON*

        throw EngineError("Unknown move category: "s + name.data());
    }

    std::string_view getMoveCategoryName(const MoveCategory category)
    {
        switch (category)
        {
            case SimulationMode::MoveCategory::PHYSICAL:
                return PHYSICAL;
            case SimulationMode::MoveCategory::SPECIAL:
                return SPECIAL;
            case SimulationMode::MoveCategory::STATUS:
                return STATUS;
        }

        throw EngineError("Unknown move category id: "s + std::to_string(static_cast<int>(category)));
    }

} // namespace SimulationMode
