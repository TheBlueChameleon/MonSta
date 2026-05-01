#ifndef TARGET_HPP
#define TARGET_HPP

#include <string_view>

namespace MetaDefinition
{
    namespace EffectParams
    {
        constexpr auto TARGET = "Target";

        constexpr auto TARGET_SELF        = "Self";
        constexpr auto TARGET_ENEMY       = "Enemy";
        constexpr auto TARGET_BOTH        = "Both";
        constexpr auto TARGET_CHOOSESELF  = "ChooseSelf";
        constexpr auto TARGET_CHOOSEENEMY = "ChooseEnemy";
        constexpr auto TARGET_RANDOMSELF  = "RandomSelf";
        constexpr auto TARGET_RANDOMENEMY = "RandomEnemy";

        enum class Target {Self, Enemy, Both, ChooseSelf, ChooseEnemy, RandomSelf, RandomEnemy};

        Target getTargetFromName(const std::string_view name);
        std::string_view getTargetName(const Target target);

    }   // namespace EffectParams
}       // namespace MetaDefinition

#endif // TARGET_HPP
