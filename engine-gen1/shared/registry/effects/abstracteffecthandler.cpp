#include <base/errorbuffer.hpp>

#include "abstracteffecthandler.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    using namespace EffectParams;

    void AbstractEffectHandler::assertOnlySupportedParams(
        const KeySet& supportedParamKeys,
        const KeyValueMap& actualParams
    )
    {
        EngineBase::ErrorBuffer eb;
        for (const std::pair<std::string, std::string>& kvPair : actualParams)
        {
            if (!supportedParamKeys.contains(kvPair.first))
            {
                eb.append(
                    ApiStatusCode::INVALID_USER_INPUT,
                    ""s + kvPair.first
                );
            }
        }

        if (!eb.isClean())
        {
            throw EngineError(
                ApiStatusCode::INVALID_USER_INPUT,
                eb.compileErrorMessage()
            );
        }
    }

    Target AbstractEffectHandler::extractTarget(
        const KeyValueMap& params,
        const EffectParams::Target defaultValue
    )
    {
        const auto it = params.find(TARGET);
        if (it == params.end())
        {
            return defaultValue;
        }
        else
        {
            const auto value = it->second;
            return getTargetFromName(value);
        }
    }

    std::pair<NumberInterpretation, double> AbstractEffectHandler::extractEffectStrength(const KeyValueMap& params)
    {
        auto it = params.find(PERCENTAGE);
        if (it != params.end())
        {
            return std::make_pair(NumberInterpretation::Percentage, std::stod(it->second));
        }

        it = params.find(ABSOLUTE);
        if (it != params.end())
        {
            return std::make_pair(NumberInterpretation::Absolute, std::stod(it->second));
        }

        throw EngineError(
            ApiStatusCode::INVALID_USER_INPUT,
            "Parameters for effect Drain contain neither "s + PERCENTAGE + " nor " + ABSOLUTE
        );
    }
}
