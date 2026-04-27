#include <base/errorbuffer.hpp>

#include "abstracteffecthandler.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    using namespace EffectParams;

    void AbstractEffectHandler::missingParameter(
        const std::string_view effectName,
        const std::string_view paramName
    )
    {
        throw EngineError(
            ApiStatusCode::INVALID_USER_INPUT,
            "Effect '"s + effectName.data() + "' needs a parameter '" + paramName.data() + "'"
        );
    }

    void AbstractEffectHandler::assertOnlySupportedParams(
        const std::string_view effectName,
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
                    "Effect '"s + effectName.data() + "' does not support parameter '" + kvPair.first + "'"
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
        const std::string_view effectName,
        const KeyValueMap& params
    )
    {
        const auto it = params.find(TARGET);
        if (it == params.end())
        {
            missingParameter(effectName, TARGET);
        }
        else
        {
            const auto value = it->second;
            return getTargetFromName(value);
        }

    }

    Target AbstractEffectHandler::extractTarget(
        const std::string_view effectName,
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

    HPAmount AbstractEffectHandler::extractHPAmount(
        const std::string_view effectName,
        const KeyValueMap& params
    )
    {
        auto it = params.find(HP_PERCENTAGE);
        if (it != params.end())
        {
            return {HPBasis::Percentage, std::stod(it->second)};
        }

        it = params.find(HP_ABSOLUTE);
        if (it != params.end())
        {
            return {HPBasis::Absolute, std::stod(it->second)};
        }

        throw EngineError(
            ApiStatusCode::INVALID_USER_INPUT,
            "Parameters for effect Drain contain neither "s + HP_PERCENTAGE + " nor " + HP_ABSOLUTE
        );
    }
}
