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

            mechanicsDefinition.levelCap        = md.navigateTo(JKEY_MECHANICS_LEVELCAP).getAsInteger();
            mechanicsDefinition.statsMin        = md.navigateTo(JKEY_MECHANICS_STATSMIN).getAsInteger();
            mechanicsDefinition.statsMax        = md.navigateTo(JKEY_MECHANICS_STATSMAX).getAsInteger();
            mechanicsDefinition.teamSizeMax     = md.navigateTo(JKEY_MECHANICS_TEAMSIZEMAX).getAsInteger();
            mechanicsDefinition.dvCap           = md.navigateTo(JKEY_MECHANICS_DVCAP).getAsInteger();
            mechanicsDefinition.dvSumCap        = md.navigateTo(JKEY_MECHANICS_DVSUMCAP).getAsInteger();
            mechanicsDefinition.statExpCap      = md.navigateTo(JKEY_MECHANICS_STATEXPCAP).getAsInteger();
            mechanicsDefinition.statExpSumCap   = md.navigateTo(JKEY_MECHANICS_STATEXPSUMCAP).getAsInteger();
            mechanicsDefinition.obedience       = md.navigateTo(JKEY_MECHANICS_OBEDIENCE).getAsBool();
            mechanicsDefinition.gen1miss        = md.navigateTo(JKEY_MECHANICS_GEN1MISS).getAsBool();

            mechanicsDefinition.bideGlitch                  = md.navigateTo(JKEY_MECHANICS_BIDE_GLITCH).getAsBool();
            mechanicsDefinition.counterGlitch               = md.navigateTo(JKEY_MECHANICS_COUNTERGLITCH).getAsBool();
            mechanicsDefinition.critRateGlitch              = md.navigateTo(JKEY_MECHANICS_CRITRATEGLITCH).getAsBool();
            mechanicsDefinition.experienceUnderflowGlitch   = md.navigateTo(JKEY_MECHANICS_EXPUNDERFLOWGLITCH).getAsBool();
            mechanicsDefinition.hpRecoveryGlitch            = md.navigateTo(JKEY_MECHANICS_HPRECOVERYGLITCH).getAsBool();
            mechanicsDefinition.hyperbeamFreezeGlitch       = md.navigateTo(JKEY_MECHANICS_HYPERBEAMFREEZEGLITCH).getAsBool();
            mechanicsDefinition.hyperbeamSleepGlitch        = md.navigateTo(JKEY_MECHANICS_HYPERBEAMSLEEPGLITCH).getAsBool();
            mechanicsDefinition.invulnerabilityGlitch       = md.navigateTo(JKEY_MECHANICS_INVULNERABILITYGLITCH).getAsBool();
            mechanicsDefinition.jumpKickGlitch              = md.navigateTo(JKEY_MECHANICS_JUMPKICKGLITCH).getAsBool();
            mechanicsDefinition.mimicLevelUpGlitch          = md.navigateTo(JKEY_MECHANICS_MIMICLEVELUPGLITCH).getAsBool();
            mechanicsDefinition.statusModificationGlitch    = md.navigateTo(JKEY_MECHANICS_STATMODGLITCH).getAsBool();
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
