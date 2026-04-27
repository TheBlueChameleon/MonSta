#ifndef HPAMOUNT_H
#define HPAMOUNT_H

#include <string_view>

namespace MetaDefinition
{
    namespace EffectParams
    {
        constexpr auto HP_ABSOLUTE   = "HP";
        constexpr auto HP_PERCENTAGE = "HP%";

        enum class HPBasis {Absolute, Percentage};

        HPBasis getHPBasisFromName(const std::string_view name);
        std::string_view getHPBasisName(const HPBasis numberInterpretation);

        struct HPAmount
        {
            HPBasis basis;
            double  value;
        };

    }   // namespace EffectParams
}       // namespace MetaDefinition

#endif // HPAMOUNT_H
