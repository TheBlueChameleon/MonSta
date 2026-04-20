#include <algorithm>
#include <iostream>

#include <base/errors.hpp>

#include "typechart.hpp"

using namespace std::string_literals;
namespace SimulationMode
{
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

    void TypeChart::show() const
    {
        for (const auto& row : table)
        {
            for (const auto d : row)
            {
                std::cout << d << "\t";
            }
            std::cout << std::endl;
        }
    }

}
