#include "shared/registry/registry.hpp"

#include "move.hpp"

namespace MetaDefinition
{
    Move::Move() {}

    int Move::getPower() const
    {
        return 0;
    }

    std::string_view Move::getType() const
    {
        return "Normal";
    }

    size_t Move::getTypeID() const
    {
        return 0;
    }

    MoveCategory Move::getCategory() const
    {
        return Registry::typeChart.getMoveCategoryForType(getType());
    }

} // namespace SimulationMode
