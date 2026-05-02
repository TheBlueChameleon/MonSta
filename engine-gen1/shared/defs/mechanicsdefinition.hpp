#ifndef MECHANICSDEFINITION_HPP
#define MECHANICSDEFINITION_HPP

namespace MetaDefinition
{
    struct MechanicsDefinition
    {
        int levelCap;
        int statsMin;
        int statsMax;
        int teamSizeMax;
        int dvCap;
        int dvSumCap;
        int statExpCap;
        int statExpSumCap;
        int obedienceCap;
        int sleepMinTurns;
        int sleepMaxTurns;
        int confusionMinTurns;
        int confusionMaxTurns;
        int confusionHitChance;
        int confusionHitStrength;
        double burnDamagePercentage;

        bool gen1miss;
        bool bideGlitch;
        bool counterGlitch;
        bool critRateGlitch;
        bool experienceUnderflowGlitch;
        bool hpRecoveryGlitch;
        bool hyperbeamFreezeGlitch;
        bool hyperbeamSleepGlitch;
        bool invulnerabilityGlitch;
        bool mimicLevelUpGlitch;
        bool badgeBoostGlitch;
        bool substituteHpDrainGlitch;
        bool substituteSelfHurtGlitch;
        bool toxicLeechSeedGlitch;
        bool toxicRestGlitch;
        bool opponentFaintSkipGlitch;
    };
}

#endif // MECHANICSDEFINITION_HPP
