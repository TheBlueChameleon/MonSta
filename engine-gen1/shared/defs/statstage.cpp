#include <base/errors.hpp>

#include "statstage.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    StatStage getStatStageFromName(const std::string_view name)
    {
            // *INDENT-OFF*
            if      (name == STATSTAGE_ATK)      { return StatStage::ATK;      }
            else if (name == STATSTAGE_DEF)      { return StatStage::DEF;      }
            else if (name == STATSTAGE_SPC)      { return StatStage::SPC;      }
            else if (name == STATSTAGE_SPD)      { return StatStage::SPD;      }
            else if (name == STATSTAGE_ACCURACY) { return StatStage::Accuracy; }
            else if (name == STATSTAGE_EVASION)  { return StatStage::Evasion;  }
            else if (name == STATSTAGE_CRITRATE) { return StatStage::CritRate; }
            else { throw  IllegalArgumentError("Unknown StatStage: '"s + name.data() + "'");}
            // *INDENT-ON*
    }

    std::string_view getStatStageName(const StatStage statStage)
    {
        switch (statStage)
        {
            case StatStage::ATK:
                return STATSTAGE_ATK;
            case StatStage::DEF:
                return STATSTAGE_DEF;
            case StatStage::SPC:
                return STATSTAGE_SPC;
            case StatStage::SPD:
                return STATSTAGE_SPD;
            case StatStage::Accuracy:
                return STATSTAGE_ACCURACY;
            case StatStage::Evasion:
                return STATSTAGE_EVASION;
            case StatStage::CritRate:
                return STATSTAGE_CRITRATE;
        }
        throw  IllegalArgumentError(
            "Unknown StatStage ID: "s + std::to_string(static_cast<int>(statStage))
        );
    }

    SimulationMode::StatStage getSimulationModeValue(const StatStage statStage)
    {
        switch (statStage)
        {
            case StatStage::ATK:
                return SimulationMode::StatStage::ATK;
            case StatStage::DEF:
                return SimulationMode::StatStage::DEF;
            case StatStage::SPC:
                return SimulationMode::StatStage::SPC;
            case StatStage::SPD:
                return SimulationMode::StatStage::SPD;
            case StatStage::Accuracy:
                return SimulationMode::StatStage::Accuracy;
            case StatStage::Evasion:
                return SimulationMode::StatStage::Evasion;
            case StatStage::CritRate:
                return SimulationMode::StatStage::CritRate;
        }
        throw  IllegalArgumentError(
            "Unknown StatStage ID: "s + std::to_string(static_cast<int>(statStage))
        );
    }

} // namespace MetaDefinition
