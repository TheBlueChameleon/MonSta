#include <base/errors.hpp>

#include "hpamount.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    namespace EffectParams
    {
        HPBasis getHPBasisFromName(const std::string_view name)
        {
            // *INDENT-OFF*
            if      (name == HP_ABSOLUTE)   { return HPBasis::Absolute;  }
            else if (name == HP_PERCENTAGE) { return HPBasis::Percentage; }
            else                         { throw  EngineError(ApiStatusCode::ILLEGAL_CLIENT_STATE, "Unknown NumberInterpretation: '"s + name.data() + "'");}
            // *INDENT-ON*
        }

        std::string_view getHPBasisName(const HPBasis numberInterpretation)
        {
            switch (numberInterpretation)
            {
                case HPBasis::Absolute:
                    return HP_ABSOLUTE;
                case HPBasis::Percentage:
                    return HP_PERCENTAGE;
            }

            throw  EngineError(
                ApiStatusCode::ILLEGAL_CLIENT_STATE,
                "Unknown integer interpretation code: "s + std::to_string(static_cast<int>(numberInterpretation))
            );
        }

    }   // namespace EffectParams
}       // namespace MetaDefinition
