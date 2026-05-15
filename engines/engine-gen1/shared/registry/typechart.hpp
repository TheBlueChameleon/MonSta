#ifndef TYPECHART_HPP
#define TYPECHART_HPP

#include <span>
#include <string>
#include <vector>
#include <unordered_map>

#include "shared/defs/typeinfo.hpp"

namespace Registry
{
    class TypeChart
    {
        public:
            static constexpr auto ATTACKER = "Attacker";
            static constexpr auto CATEGORY = "Category";

        private:
            std::unordered_map<std::string, size_t> indices;
            std::vector<std::vector<double>>        table;
            std::vector<std::string>                names;
            std::vector<MetaDefinition::MoveCategory> moveCategories;

        public:
            TypeChart() = default;

            void setupTypes(const std::vector<std::string_view>& columnNames);
            void setRow(const std::string_view typeName, const MetaDefinition::MoveCategory category, const std::vector<std::string_view>& effectiveness);

            const std::string& getTypeName(const size_t index) const;
            size_t getIndex(const std::string_view typeName) const;

            const MetaDefinition::MoveCategory getMoveCategoryForType(const std::string_view type);
            const MetaDefinition::MoveCategory getMoveCategoryForTypeID(const size_t typeID);
            double getMultiplier(const size_t attackerTypeID, const size_t defenderTypeID) const;
            double getMultiplier(const std::string_view attackerTypeName, const std::string_view defenderTypeName) const;
            double getMultiplier(const std::string_view attackerTypeName, const MetaDefinition::PokemonType& defenderType) const;
            double getMultiplier(const size_t attackerTypeID, const MetaDefinition::PokemonTypeID defenderTypeId) const;
    };
}

#endif // TYPECHART_HPP
