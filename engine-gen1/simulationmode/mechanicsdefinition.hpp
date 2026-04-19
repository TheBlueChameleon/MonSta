#ifndef MECHANICSDEFINITION_H
#define MECHANICSDEFINITION_H

struct MechanicsDefinition
{
    int levelCap;
    int statsMin;
    int statsMax;
    bool obedience;
    bool gen1miss;
    bool bideGlitch;
    bool counterGlitch;
    bool critRateGlitch;
    bool experienceUnderflowGlitch;
    bool hpRecoveryGlitch;
    bool hyperbeamFreezeGlitch;
    bool hyperbeamSleepGlitch;
    bool invulnerabilityGlitch;
    bool jumpKickGlitch;
    bool mimicLevelUpGlitch;
    bool statusModificationGlitch;
    bool substituteHpDrainGlitch;
    bool substituteSelfHurtGlitch;
    bool toxicLeechSeedGlitch;
    bool toxicRestGlitch;
};

#endif // MECHANICSDEFINITION_H
