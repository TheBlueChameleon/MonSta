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

        switch (move.getCategory())
        {
            case MetaDefinition::MoveCategory::PHYSICAL:
                result.offense = attacker.getStat(Stat::ATK);
                result.defense = defender.getStat(Stat::DEF);
                result.unboostedOffense = attacker.getInitialStat(Stat::ATK);
                result.unboostedDefense = defender.getInitialStat(Stat::DEF);
                break;

            case MetaDefinition::MoveCategory::SPECIAL:
                result.offense = attacker.getStat(Stat::SPC);
                result.defense = defender.getStat(Stat::SPC);
                result.unboostedOffense = attacker.getInitialStat(Stat::SPC);
                result.unboostedDefense = defender.getInitialStat(Stat::SPC);
                break;

            case MetaDefinition::MoveCategory::STATUS:
                return result;
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

        if (attacker.getIgnoreMoveType())
        {
            result.typeMultiplier = 1.0;
            result.stabMultiplier = 1.0;
        }
        else
        {
            const auto typeMove = move.getTypeID();
            const auto typeDefender = defender.getEffectiveTypeID();
            const auto typeAttacker = attacker.getEffectiveTypeID();
            result.typeMultiplier = Registry::typeChart.getMultiplier(typeMove, typeDefender);
            result.stabMultiplier = 1.0 + (typeAttacker.matches(typeMove) * 0.5);
        }

        return result;
    }

    int getDamageMaxWithHardwareEmulatuion(const DamageInfo& damageInfo)
    {
        int offense;
        int defense;

        if (damageInfo.criticalHit)
        {
            offense = damageInfo.offense;
            defense = damageInfo.defense;
        }
        else
        {
            offense = damageInfo.unboostedOffense;
            defense = damageInfo.unboostedDefense;
            defense <<= damageInfo.screen;
        }

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

        const int d0 = (2 * damageInfo.level * (1 + damageInfo.criticalHit)) / 5;
        const int d1 = (d0 + 2) * damageInfo.power * offense;
        const int d2 = d1 / defense;
        const int d3 = (d2 / 50) + 2;
        const int d4 = d3 * damageInfo.stabMultiplier;
        const int d5 = d4 * damageInfo.typeMultiplier;
        return std::max(1, d5);
    }

    int getDamageMaxWithoutHardwareEmulatuion(const DamageInfo& damageInfo)
    {
        double offense = (damageInfo.criticalHit ? damageInfo.unboostedOffense : damageInfo.offense);
        double defense = (damageInfo.criticalHit ? damageInfo.unboostedDefense : damageInfo.defense);

        defense /= static_cast<double>(damageInfo.screen + 1);
        defense += (defense == 0);

        const double d0 = (2 * damageInfo.level * (1 + damageInfo.criticalHit)) / 5.0;
        const double d1 = (d0 + 2.0) * damageInfo.power * offense;
        const double d2 = d1 / defense;
        const double d3 = (d2 / 50.0) + 2.0;
        const double d4 = d3 * damageInfo.stabMultiplier * damageInfo.typeMultiplier;
        return std::max(1, d4);
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
        const int withRngDenominator = dMax * RngService::getIntBetween(217, 255);
        return std::max(1, withRngDenominator / 255);
    }

} // namespace SimulationMode
