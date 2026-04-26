#ifndef MOVE_HPP
#define MOVE_HPP

namespace MetaDefinition
{
    class Move
    {
        public:
            static constexpr auto NAME          = "Name";
            static constexpr auto TYPE          = "Type";
            static constexpr auto PP            = "PP";
            static constexpr auto POWER         = "Power";
            static constexpr auto ACCURACY      = "Accuracy";
            static constexpr auto PRIORITY      = "Priority";
            static constexpr auto EFFECT        = "Effect";
            static constexpr auto EFFECT_CHANCE = "EffectChance";

        public:
            Move();
    };

} // namespace SimulationMode

#endif // MOVE_HPP
