#ifndef TYPECHART_HPP
#define TYPECHART_HPP

namespace SimulationMode
{
    class TypeChart
    {
        public:
            static constexpr auto PHYSICAL = "physical";
            static constexpr auto SPECIAL  = "special";
            static constexpr auto ATTACKER = "Attacker";
            static constexpr auto CATEGORY = "Category";

        private:
        public:
            TypeChart();
    };
}

#endif // TYPECHART_HPP
