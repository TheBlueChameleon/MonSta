#include <iostream>

#include "services/loggerservice.hpp"
#include "services/jsonservice.hpp"

#include "base/enginebase.hpp"

#include "globals.hpp"
#include "schemavalidationconstants.hpp"

#include "registry.hpp"
#include "simulationmode.hpp"

using namespace EngineBase;

namespace SimulationMode
{
    static int getInt(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer
    )
    {
        const auto targetHandle = JsonService::navigateTo(handle, jsonPointer);
        return JsonService::getAsInteger(targetHandle);
    }

    static bool getFlag(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer
    )
    {
        const auto targetHandle = JsonService::navigateTo(handle, jsonPointer);
        return JsonService::getAsBool(targetHandle);
    }

    void loadAndRegisterMechanicsDefinition(
        const std::filesystem::path& mechanicsDefinitionFile,
        ErrorBuffer& eb
    )
    {
        using namespace SchemaValidation;

        try
        {
            LoggerService::traceF("loading mechanics definitions from '{}'", mechanicsDefinitionFile.c_str());

            std::string mechanicsHandleName = Globals::jtag_base + mechanicsDefinitionFile.c_str();
            JHND_MECHANICSDEFINITION = JsonService::readValidatePatchAndAdd(
                                           IJsonServiceTypes::JsonTag(mechanicsHandleName.data()),
                                           mechanicsDefinitionFile,
                                           SchemaValidation::JTAG_MECHANICSDEFINITION
                                       );

            mechanicsDefinition.levelCap    = getInt(JHND_MECHANICSDEFINITION,  JKEY_MECHANICS_LEVELCAP);
            mechanicsDefinition.statsMin    = getInt(JHND_MECHANICSDEFINITION,  JKEY_MECHANICS_STATSMIN);
            mechanicsDefinition.statsMax    = getInt(JHND_MECHANICSDEFINITION,  JKEY_MECHANICS_STATSMAX);
            mechanicsDefinition.obedience   = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_OBEDIENCE);
            mechanicsDefinition.gen1miss    = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_GEN1MISS);

            mechanicsDefinition.bideGlitch                  = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_BIDE_GLITCH);
            mechanicsDefinition.counterGlitch               = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_COUNTERGLITCH);
            mechanicsDefinition.critRateGlitch              = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_CRITRATEGLITCH);
            mechanicsDefinition.experienceUnderflowGlitch   = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_EXPUNDERFLOWGLITCH);
            mechanicsDefinition.hpRecoveryGlitch            = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_HPRECOVERYGLITCH);
            mechanicsDefinition.hyperbeamFreezeGlitch       = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_HYPERBEAMFREEZEGLITCH);
            mechanicsDefinition.hyperbeamSleepGlitch        = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_HYPERBEAMSLEEPGLITCH);
            mechanicsDefinition.invulnerabilityGlitch       = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_INVULNERABILITYGLITCH);
            mechanicsDefinition.jumpKickGlitch              = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_JUMPKICKGLITCH);
            mechanicsDefinition.mimicLevelUpGlitch          = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_MIMICLEVELUPGLITCH);
            mechanicsDefinition.statusModificationGlitch    = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_STATMODGLITCH);
            mechanicsDefinition.substituteHpDrainGlitch     = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_SUBSTITUTEHPDRAINGLITCH);
            mechanicsDefinition.substituteSelfHurtGlitch    = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_SUBSTITUTESELFHURTGLITCH);
            mechanicsDefinition.toxicLeechSeedGlitch        = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_TOXICLEECHSEEDGLITCH);
            mechanicsDefinition.toxicRestGlitch             = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_TOXICRESTGLITCH);
        }
        catch (const EngineError& e)
        {
            eb.append(e);
        }
    }

    void setupSimulationMode(const IMatchDefinition& matchDefinition)
    {
        ErrorBuffer eb;
        LoggerService::debug("setup for simulation mode started...");

        loadAndRegisterMechanicsDefinition(matchDefinition.mechanics, eb);

        if (!eb.isClean())
        {
            throw EngineError(eb.compileErrorMessage().data());
        }

        LoggerService::debug("... done");
    }
}
