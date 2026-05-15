#include <algorithm>

#include <base/errors.hpp>

#include "typechart.hpp"

using namespace std::string_literals;
using namespace MetaDefinition;

namespace Registry
{
    void TypeChart::setupTypes(const std::vector<std::string_view>& columnNames)
    {
        indices.clear();

        moveCategories = std::vector<MoveCategory>(columnNames.size());
        names          = std::vector<std::string> (columnNames.size());

        size_t i = 0;
        for (const auto typeName : columnNames)
        {
            indices[typeName.data()] = i;
            names[i] = typeName;
            moveCategories[i] = MoveCategory::PHYSICAL;
            ++i;
        }

        table = std::vector(columnNames.size(), std::vector(columnNames.size(), 0.0));
    }

    void TypeChart::setRow(
        const std::string_view typeName,
        const MoveCategory category,
        const std::vector<std::string_view>& effectiveness
    )
    {
        const size_t typeID = getIndex(typeName);
        if (table.size() != effectiveness.size())
        {
            throw IllegalArgumentError("Mismatched input: expected "s +
                                       std::to_string(table.size()) + " columns but got " +
                                       std::to_string(effectiveness.size())
                                      );
        }

        std::vector<double>& targetRow = table[typeID];
        const auto converter = [](const auto cell)
        {
            return std::stod(cell.data());
        };
        std::transform(effectiveness.begin(), effectiveness.end(),
                       targetRow.begin(),
                       converter
                      );

        moveCategories[typeID] = category;
    }

    const std::string& TypeChart::getTypeName(const size_t index) const
    {
        if (index >= names.size())
        {
            throw IllegalArgumentError("Unknown type ID: "s + std::to_string(index));
        }
        return names[index];
    }

    size_t TypeChart::getIndex(const std::string_view typeName) const
    {
        const auto it = indices.find(typeName.data());
        if (it == indices.end())
        {
            throw IllegalArgumentError("Unknown type name: "s + typeName.data());
        }
        else
        {
            // it is pair<key, value>
            return it->second;
        }
    }

    const MoveCategory TypeChart::getMoveCategoryForType(const std::string_view type)
    {
        const auto typeID = getIndex(type);
        return moveCategories[typeID];
    }

    const MoveCategory TypeChart::getMoveCategoryForTypeID(const size_t typeID)
    {
        if (typeID >= moveCategories.size())
        {
            throw IllegalArgumentError("Unknown TypeID: "s + std::to_string(typeID));
        }
        return moveCategories[typeID];
    }

    double TypeChart::getMultiplier(const size_t attackerTypeID, const size_t defenderTypeID) const
    {
        const auto N = table.size();
        if (attackerTypeID >= N)
        {
            throw IllegalArgumentError("Invalid row index: "s + std::to_string(attackerTypeID));
        }
        if (defenderTypeID >= N)        // this is a NxN table, so table.size() is valid here
        {
            throw IllegalArgumentError("Invalid column index: "s + std::to_string(defenderTypeID));
        }

        return table[attackerTypeID][defenderTypeID];
    }

    double TypeChart::getMultiplier(const std::string_view attackerTypeName, const std::string_view defenderTypeName) const
    {
        const auto atkIndex = getIndex(attackerTypeName);
        const auto defIndex = getIndex(defenderTypeName);
        return table[atkIndex][defIndex];
    }

    double TypeChart::getMultiplier(const std::string_view attackerTypeName, const PokemonType& defenderType) const
    {
        const auto attackerIndex = getIndex(attackerTypeName);
        return getMultiplier(attackerIndex, defenderType.toTypeID());
    }

    double TypeChart::getMultiplier(const size_t attackerTypeID, const MetaDefinition::PokemonTypeID defenderTypeId) const
    {
        const auto& targetRow = table[attackerTypeID];

        double result = targetRow[defenderTypeId.primary];
        if (defenderTypeId.secondary.has_value())
        {
            result *= targetRow[defenderTypeId.secondary.value()];
        }

        return result;
    }

}
