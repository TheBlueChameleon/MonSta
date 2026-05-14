#include <base/errors.hpp>

#include "shared/registry/registry.hpp"

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

    bool PokemonType::matches(const std::string_view other) const
    {
        if (primary == other)
        {
            return true;
        }

        if (secondary.has_value())
        {
            if (secondary.value() == other)
            {
                return true;
            }
        }

        return false;
    }

    PokemonTypeID PokemonType::toTypeID() const
    {
        const size_t primaryID = Registry::typeChart.getIndex(primary);
        std::optional<size_t> secondaryID;
        if (secondary.has_value())
        {
            secondaryID = Registry::typeChart.getIndex(secondary.value());
        }

        return PokemonTypeID {primaryID, secondaryID};
    }

    bool PokemonTypeID::matches(const size_t other) const
    {
        if (primary == other)
        {
            return true;
        }

        if (secondary.has_value())
        {
            if (secondary.value() == other)
            {
                return true;
            }
        }

        return false;
    }

    PokemonType PokemonTypeID::toType() const
    {
        const std::string primaryID = Registry::typeChart.getTypeName(primary);
        std::optional<std::string> secondaryID;
        if (secondary.has_value())
        {
            secondaryID = Registry::typeChart.getTypeName(secondary.value());
        }

        return PokemonType {primaryID, secondaryID};
    }

} // namespace SimulationMode
