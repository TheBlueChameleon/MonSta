#ifndef STAT_HPP
#define STAT_HPP

#include <string_view>

namespace MetaDefinition
{
    constexpr auto STAT_HP  = "HP";
    constexpr auto STAT_ATK = "ATK";
    constexpr auto STAT_DEF = "DEF";
    constexpr auto STAT_SPC = "SPC";
    constexpr auto STAT_SPD = "SPD";

    enum class Stat {HP, ATK, DEF, SPC, SPD};

    Stat getStatFromName(const std::string_view name);
    std::string_view getStatName(const Stat stat);
}

#endif // STAT_HPP
