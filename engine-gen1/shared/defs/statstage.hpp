#ifndef PARAMS_STATSTAGE_HPP
#define PARAMS_STATSTAGE_HPP

#include <string_view>

#include "simulationmode/arena/statstage.hpp"

namespace MetaDefinition
{
    constexpr auto STAGE = "Stage";

    constexpr auto STATSTAGE_ATK      = "ATK";
    constexpr auto STATSTAGE_DEF      = "DEF";
    constexpr auto STATSTAGE_SPC      = "SPC";
    constexpr auto STATSTAGE_SPD      = "SPD";
    constexpr auto STATSTAGE_ACCURACY = "Accuracy";
    constexpr auto STATSTAGE_EVASION  = "Evasion";
    constexpr auto STATSTAGE_CRITRATE = "CritRate";

    enum class StatStage {ATK, DEF, SPC, SPD, Accuracy, Evasion, CritRate};

    StatStage getStatStageFromName(const std::string_view name);
    std::string_view getStatStageName(const StatStage statStage);

    SimulationMode::StatStage getSimulationModeValue(const StatStage statStage);

} // namespace MetaDefinition

#endif // PARAMS_STATSTAGE_HPP
