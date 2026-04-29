#ifndef HPAMOUNT_HPP
#define HPAMOUNT_HPP

#include <string_view>

namespace MetaDefinition
{
    namespace EffectParams
    {
        constexpr auto HPAMOUNT_ABSOLUTE   = "HP";
        constexpr auto HPAMOUNT_PERCENTAGE = "HP%";

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

#endif // HPAMOUNT_HPP
