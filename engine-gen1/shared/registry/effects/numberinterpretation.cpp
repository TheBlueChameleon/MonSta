#include <base/errors.hpp>

#include "numberinterpretation.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    NumberInterpretation getNumberInterpretationFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if      (name == ABSOLUTE)   { return NumberInterpretation::Absolute;  }
        else if (name == PERCENTAGE) { return NumberInterpretation::Percentage; }
        else                         { throw  EngineError(ApiStatusCode::ILLEGAL_CLIENT_STATE, "Unknown integer interpretation: '"s + name.data() + "'");}
        // *INDENT-ON*
    }

    std::string_view getNumberInterpretationName(const NumberInterpretation numberInterpretation)
    {
        switch (numberInterpretation)
        {
            case MetaDefinition::NumberInterpretation::Absolute:
                return ABSOLUTE;
            case MetaDefinition::NumberInterpretation::Percentage:
                return PERCENTAGE;
        }

        throw  EngineError(
            ApiStatusCode::ILLEGAL_CLIENT_STATE,
            "Unknown integer interpretation code: "s + std::to_string(static_cast<int>(numberInterpretation))
        );
    }

} // namespace MetaDefinition
