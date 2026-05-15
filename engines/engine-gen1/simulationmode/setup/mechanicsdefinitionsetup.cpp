#include <base/errorbuffer.hpp>

#include <services/jsonservice.hpp>
#include <services/loggerservice.hpp>

#include "shared/schemavalidationconstants.hpp"
#include "shared/registry/registry.hpp"

#include "setuperrorhandling.hpp"

using namespace std::string_literals;
using namespace EngineBase;
using namespace Registry;
using namespace SchemaValidation;

namespace SimulationMode
{
    void loadAndRegisterMechanicsDefinition(
        const std::filesystem::path& mechanicsDefinitionFile,
        ErrorBuffer& eb
    )
    {
        try
        {
            LoggerService::traceF("  ... loading mechanics definition from '{}'", mechanicsDefinitionFile.c_str());

            std::string mechanicsHandleName = jtag_base + mechanicsDefinitionFile.c_str();
            JHND_MECHANICSDEFINITION = JsonService::readValidatePatchAndAdd(
                                           IJsonServiceTypes::JsonTag(mechanicsHandleName.data()),
                                           mechanicsDefinitionFile,
                                           JTAG_MECHANICSDEFINITION
                                       );
            JsonService::JsonWrapper md = (JHND_MECHANICSDEFINITION);

            mechanicsDefinition.levelCap                = md.navigateTo(JKEY_MECHANICS_LEVELCAP).getAsInteger();
            mechanicsDefinition.statsMin                = md.navigateTo(JKEY_MECHANICS_STATSMIN).getAsInteger();
            mechanicsDefinition.statsMax                = md.navigateTo(JKEY_MECHANICS_STATSMAX).getAsInteger();
            mechanicsDefinition.teamSizeMax             = md.navigateTo(JKEY_MECHANICS_TEAMSIZEMAX).getAsInteger();
            mechanicsDefinition.dvCap                   = md.navigateTo(JKEY_MECHANICS_DVCAP).getAsInteger();
            mechanicsDefinition.dvSumCap                = md.navigateTo(JKEY_MECHANICS_DVSUMCAP).getAsInteger();
            mechanicsDefinition.statExpCap              = md.navigateTo(JKEY_MECHANICS_STATEXPCAP).getAsInteger();
            mechanicsDefinition.statExpSumCap           = md.navigateTo(JKEY_MECHANICS_STATEXPSUMCAP).getAsInteger();
            mechanicsDefinition.obedienceCap            = md.navigateTo(JKEY_MECHANICS_OBEDIENCECAP).getAsInteger();
            mechanicsDefinition.sleepMinTurns           = md.navigateTo(JKEY_MECHANICS_SLEEPMINTURNS).getAsInteger();
            mechanicsDefinition.sleepMaxTurns           = md.navigateTo(JKEY_MECHANICS_SLEEPMAXTURNS).getAsInteger();
            mechanicsDefinition.fullParalysisChance     = md.navigateTo(JKEY_MECHANICS_FULLPARALYSISCHANCE).getAsFloat() / 100.0;
            mechanicsDefinition.confusionMinTurns       = md.navigateTo(JKEY_MECHANICS_CONFUSIONMINTURNS).getAsInteger();
            mechanicsDefinition.confusionMaxTurns       = md.navigateTo(JKEY_MECHANICS_CONFUSIONMAXTURNS).getAsInteger();
            mechanicsDefinition.confusionHitChance      = md.navigateTo(JKEY_MECHANICS_CONFUSIONHITCHANCE).getAsFloat() / 100.0;
            mechanicsDefinition.confusionHitStrength    = md.navigateTo(JKEY_MECHANICS_CONFUSIONHITSTRENGTH).getAsInteger();
            mechanicsDefinition.burnDamagePercentage    = md.navigateTo(JKEY_MECHANICS_BURNDAMAGEPERCENTAGE).getAsFloat() / 100.0;
            mechanicsDefinition.poisonDamagePercentage  = md.navigateTo(JKEY_MECHANICS_POISONDAMAGEPERCENTAGE).getAsFloat() / 100.0;
            mechanicsDefinition.toxicCounterMax         = md.navigateTo(JKEY_MECHANICS_TOXICCOUNTERMAX).getAsInteger();
            mechanicsDefinition.leechSeedPercentage     = md.navigateTo(JKEY_MECHANICS_LEECHSEEDPERCENTAGE).getAsFloat() / 100.0;

            mechanicsDefinition.gen1miss                    = md.navigateTo(JKEY_MECHANICS_GEN1MISS).getAsBool();
            mechanicsDefinition.badgeBoostGlitch            = md.navigateTo(JKEY_MECHANICS_BADGEBOOSTGLITCH).getAsBool();
            mechanicsDefinition.bideGlitch                  = md.navigateTo(JKEY_MECHANICS_BIDE_GLITCH).getAsBool();
            mechanicsDefinition.counterGlitch               = md.navigateTo(JKEY_MECHANICS_COUNTERGLITCH).getAsBool();
            mechanicsDefinition.critRateGlitch              = md.navigateTo(JKEY_MECHANICS_CRITRATEGLITCH).getAsBool();
            mechanicsDefinition.damageUnderflowGlitch       = md.navigateTo(JKEY_MECHANICS_DAMAGEUNDERFLOWGLITCH).getAsBool();
            mechanicsDefinition.experienceUnderflowGlitch   = md.navigateTo(JKEY_MECHANICS_EXPUNDERFLOWGLITCH).getAsBool();
            mechanicsDefinition.hpRecoveryGlitch            = md.navigateTo(JKEY_MECHANICS_HPRECOVERYGLITCH).getAsBool();
            mechanicsDefinition.hyperbeamFreezeGlitch       = md.navigateTo(JKEY_MECHANICS_HYPERBEAMFREEZEGLITCH).getAsBool();
            mechanicsDefinition.hyperbeamSleepGlitch        = md.navigateTo(JKEY_MECHANICS_HYPERBEAMSLEEPGLITCH).getAsBool();
            mechanicsDefinition.invulnerabilityGlitch       = md.navigateTo(JKEY_MECHANICS_INVULNERABILITYGLITCH).getAsBool();
            mechanicsDefinition.mimicLevelUpGlitch          = md.navigateTo(JKEY_MECHANICS_MIMICLEVELUPGLITCH).getAsBool();
            mechanicsDefinition.opponentFaintSkipGlitch     = md.navigateTo(JKEY_MECHANICS_OPPONENTFAINTSKIPGLITCH).getAsBool();
            mechanicsDefinition.substituteHpDrainGlitch     = md.navigateTo(JKEY_MECHANICS_SUBSTITUTEHPDRAINGLITCH).getAsBool();
            mechanicsDefinition.substituteSelfHurtGlitch    = md.navigateTo(JKEY_MECHANICS_SUBSTITUTESELFHURTGLITCH).getAsBool();
            mechanicsDefinition.toxicLeechSeedGlitch        = md.navigateTo(JKEY_MECHANICS_TOXICLEECHSEEDGLITCH).getAsBool();
            mechanicsDefinition.toxicRestGlitch             = md.navigateTo(JKEY_MECHANICS_TOXICRESTGLITCH).getAsBool();
        }
        catch (const EngineError& e)
        {
            report(eb, e.what(), mechanicsDefinitionFile);
        }
    }

} // namespace SimulationMode
