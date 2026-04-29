#include <base/errors.hpp>

#include "statstage.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    namespace EffectParams
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
                case MetaDefinition::EffectParams::StatStage::ATK:
                    return STATSTAGE_ATK;
                case MetaDefinition::EffectParams::StatStage::DEF:
                    return STATSTAGE_DEF;
                case MetaDefinition::EffectParams::StatStage::SPC:
                    return STATSTAGE_SPC;
                case MetaDefinition::EffectParams::StatStage::SPD:
                    return STATSTAGE_SPD;
                case MetaDefinition::EffectParams::StatStage::Accuracy:
                    return STATSTAGE_ACCURACY;
                case MetaDefinition::EffectParams::StatStage::Evasion:
                    return STATSTAGE_EVASION;
                case MetaDefinition::EffectParams::StatStage::CritRate:
                    return STATSTAGE_CRITRATE;
            }
            throw  IllegalArgumentError(
                "Unknown StatStage ID: "s + std::to_string(static_cast<int>(statStage))
            );
        }

    } // namespace EffectParams
} // namespace MetaDefinition
