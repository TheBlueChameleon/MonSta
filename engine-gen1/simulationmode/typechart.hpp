#ifndef TYPECHART_HPP
#define TYPECHART_HPP

#include <span>
#include <string>
#include <vector>
#include <unordered_map>

#include "defs/typeinfo.hpp"

namespace SimulationMode
{
    class TypeChart
    {
        public:
            static constexpr auto ATTACKER = "Attacker";
            static constexpr auto CATEGORY = "Category";

        private:
            std::vector<std::vector<double>> table;
            std::unordered_map<std::string, size_t> indices;
            std::unordered_map<std::string, MoveCategory> moveCategories;

        public:
            TypeChart() = default;

            size_t getIndex(const std::string_view typeName) const;

            void setupTypes(const std::vector<std::string_view>& columnNames);
            void setRow(const std::string_view typeName, const MoveCategory category, const std::vector<std::string_view>& effectiveness);

            void show() const;
    };
}

#endif // TYPECHART_HPP
