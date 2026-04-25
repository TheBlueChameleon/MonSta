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
        moveCategories.clear();

        size_t i = 0;
        for (const auto typeName : columnNames)
        {
            indices[typeName.data()] = i;
            moveCategories[typeName.data()] = MoveCategory::PHYSICAL;
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
        const size_t row = getIndex(typeName);
        if (table.size() != effectiveness.size())
        {
            throw EngineError("Mismatched input: expected "s +
                              std::to_string(table.size()) + " columns but got " +
                              std::to_string(effectiveness.size())
                             );
        }

        std::vector<double>& targetRow = table[row];
        const auto converter = [](const auto cell)
        {
            return std::stod(cell.data());
        };
        std::transform(effectiveness.begin(), effectiveness.end(),
                       targetRow.begin(),
                       converter
                      );

        // find returns iterator: pair<key, value>
        // this iterator is guaranteed not to be end() because getIndex() succeded before
        moveCategories.find(typeName.data())->second = category;
    }

    size_t TypeChart::getIndex(const std::string_view typeName) const
    {
        const auto it = indices.find(typeName.data());
        if (it == indices.end())
        {
            throw EngineError("Unknown type name: "s + typeName.data());
        }
        else
        {
            // it is pair<key, value>
            return it->second;
        }
    }

    const MoveCategory TypeChart::getMoveCategoryForType(const std::string_view type)
    {
        const auto it = moveCategories.find(type.data());
        if (it == moveCategories.end())
        {
            throw EngineError("Unknown type: "s + type.data());
        }
        return it->second;
    }

    double TypeChart::getMultiplyer(const size_t rowIndex, const size_t columnIndex) const
    {
        if (rowIndex >= table.size())
        {
            throw EngineError("Invalid row index: "s + std::to_string(rowIndex));
        }
        if (columnIndex >= table.size())        // this is a NxN table, so table.size() is valid here
        {
            throw EngineError("Invalid column index: "s + std::to_string(columnIndex));
        }

        return table[rowIndex][columnIndex];
    }

    double TypeChart::getMultiplyer(const std::string_view attackerTypeName, const std::string_view defenderTypeName) const
    {
        const auto rowIndex = getIndex(attackerTypeName);
        const auto columnIndex = getIndex(defenderTypeName);
        return table[rowIndex][columnIndex];
    }

    double TypeChart::getMultiplyer(const std::string_view attackerTypeName, const PokemonType& defenderType) const
    {
        const auto rowIndex = getIndex(attackerTypeName);
        const auto columnIndex1 = getIndex(defenderType.primary);
        const auto& targetRow = table[rowIndex];

        double result = targetRow[columnIndex1];
        if (defenderType.secondary.has_value())
        {
            const auto columnIndex2 = getIndex(defenderType.secondary.value());
            result *= targetRow[columnIndex2];
        }

        return result;
    }

}
