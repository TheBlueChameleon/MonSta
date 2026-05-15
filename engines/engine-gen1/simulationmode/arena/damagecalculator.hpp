#ifndef DAMAGECALCULATOR_HPP
#define DAMAGECALCULATOR_HPP

namespace MetaDefinition
{
    class Move;
}

namespace SimulationMode
{
    class PokemonInstance;

    struct DamageInfo
    {
        int level;
        int power;
        int offense;
        int defense;
        int unboostedOffense;
        int unboostedDefense;
        bool screen;
        bool criticalHit;
        double stabMultiplier;
        double typeMultiplier;

        static constexpr int UNDERFLOW = -1;
    };

    DamageInfo getDamageInfoFull(const PokemonInstance& attacker, const PokemonInstance& defender, const MetaDefinition::Move& move);

    int getDamageMax(const DamageInfo& damageInfo);
    int getDamageRoll(const DamageInfo& damageInfo);

} // namespace SimulationMode

#endif // DAMAGECALCULATOR_HPP
