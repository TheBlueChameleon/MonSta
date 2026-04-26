#ifndef NUMBERINTERPRETATION_H
#define NUMBERINTERPRETATION_H

#include <string_view>

namespace MetaDefinition
{
    constexpr auto ABSOLUTE = "Absolute";
    constexpr auto PERCENTAGE = "Percentage";

    enum class NumberInterpretation {Absolute, Percentage};

    NumberInterpretation getNumberInterpretationFromName(const std::string_view name);
    std::string_view getNumberInterpretationName(const NumberInterpretation numberInterpretation);

} // namespace MetaDefinition

#endif // NUMBERINTERPRETATION_H
