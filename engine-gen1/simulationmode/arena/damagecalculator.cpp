#include <cstdint>

#include <services/rngservice.hpp>

#include "shared/registry/moves/move.hpp"
#include "shared/registry/registry.hpp"

#include "damagecalculator.hpp"
#include "pokemoninstance.hpp"

using namespace MetaDefinition;

namespace SimulationMode
{
    DamageInfo getDamageInfoFull(
        const PokemonInstance& attacker,
        const PokemonInstance& defender,
        const Move& move
    )
    {
        DamageInfo result = {};

        result.level = attacker.getLevel();
        result.power = move.getPower();

        if (move.getCategory() == MoveCategory::PHYSICAL)
        {
            result.offense = attacker.getStat(Stat::ATK);
            result.defense = defender.getStat(Stat::DEF);
            result.initOffense = attacker.getInitStat(Stat::ATK);
            result.initDefense = defender.getInitStat(Stat::DEF);
        }
        else if (move.getCategory() == MoveCategory::SPECIAL)
        {
            result.offense = attacker.getStat(Stat::SPC);
            result.defense = defender.getStat(Stat::SPC);
            result.initOffense = attacker.getInitStat(Stat::SPC);
            result.initDefense = defender.getInitStat(Stat::SPC);
        }

        const std::optional<MetaDefinition::MoveCategory> screenType = defender.getScreen();
        if (screenType.has_value())
        {
            if (move.getCategory() == screenType.value())
            {
                result.screen = true;
            }
        }

        const uint8_t critThreshold = attacker.getCritRollThreshold();
        const uint8_t roll = RngService::getIntBetween(0, 255);
        result.criticalHit = Registry::mechanicsDefinition.gen1miss ?
                             (roll <  critThreshold) :
                             (roll <= critThreshold);

        // TODO: stab

        if (attacker.getIgnoreMoveType())
        {
            result.typeMultiplier = 1.0;
            result.stab = 1.0;
        }
        else
        {
            const auto typeMove = move.getType();
            const auto typeDefender = defender.getEffectiveType();
            const auto typeAttacker = attacker.getEffectiveType();
            result.typeMultiplier = Registry::typeChart.getMultiplyer(typeMove, typeDefender);
            result.stab = 1.0 + (typeAttacker.matches(typeMove) * 0.5);
        }

        return result;
    }

    int getDamageMaxWithHardwareEmulatuion(const DamageInfo& damageInfo)
    {
        int16_t offense = (damageInfo.criticalHit ? damageInfo.initOffense : damageInfo.offense);
        int16_t defense = (damageInfo.criticalHit ? damageInfo.initDefense : damageInfo.defense);

        defense <<= damageInfo.screen;

        if (offense > 255 || defense > 255)
        {
            offense >>= 2;
            defense >>= 2;
        }

        offense &= 255;
        defense &= 255;

        if (defense == 0)
        {
            return DamageInfo::UNDERFLOW;
        }

        const int16_t d0 = (2 * damageInfo.level * (1 + damageInfo.criticalHit)) / 5;
        const int16_t d1 = (d0 + 2) * damageInfo.power * offense;
        const int16_t d2 = d1 / defense;
        const int16_t d3 = (d2 / 50) + 2;
        return d3 * damageInfo.stab * damageInfo.typeMultiplier;
    }

    int getDamageMaxWithoutHardwareEmulatuion(const DamageInfo& damageInfo)
    {
        double offense = (damageInfo.criticalHit ? damageInfo.initOffense : damageInfo.offense);
        double defense = (damageInfo.criticalHit ? damageInfo.initDefense : damageInfo.defense);

        defense /= static_cast<double>(damageInfo.screen + 1);

        if (defense == 0)
        {
            defense = 1;
        }

        const double d0 = (2 * damageInfo.level * (1 + damageInfo.criticalHit)) / 5.0;
        const double d1 = (d0 + 2.0) * damageInfo.power * offense;
        const double d2 = d1 / defense;
        const double d3 = (d2 / 50.0) + 2.0;
        return d3 * damageInfo.stab * damageInfo.typeMultiplier;
    }

    int getDamageMax(const DamageInfo& damageInfo)
    {
        if (Registry::mechanicsDefinition.damageUnderflowGlitch)
        {
            return getDamageMaxWithHardwareEmulatuion(damageInfo);
        }
        else
        {
            return getDamageMaxWithoutHardwareEmulatuion(damageInfo);
        }
    }

    int getDamageRoll(const DamageInfo& damageInfo)
    {
        const int dMax = getDamageMax(damageInfo);
        if (dMax == 1)
        {
            return 1;
        }
        const int withRngDenominator = RngService::getIntBetween(217, 255);
        return withRngDenominator / 255;
    }

} // namespace SimulationMode
