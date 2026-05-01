#include <format>
#include <sstream>

#include <base/errorbuffer.hpp>

#include "abstracteffecthandler.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    void AbstractEffectHandler::missingParameter(
        const std::string_view effectName,
        const std::string_view paramName
    )
    {
        throw MissingParameterError(
            "Effect '"s + effectName.data() + "' needs a parameter '" + paramName.data() + "'"
        );
    }

    void AbstractEffectHandler::missingParameter(
        const std::string_view effectName,
        const std::initializer_list<std::string_view> paramNames
    )
    {
        std::ostringstream namesList;
        for (const auto& paramName : paramNames)
        {
            int i = 1;
            namesList << "'" << paramName << "'";
            namesList << (i < paramNames.size() ? ", " : "");
            ++i;
        }
        throw MissingParameterError(
            "Effect '"s + effectName.data() + "' needs one of the following parameters: " + namesList.str()
        );
    }

    void AbstractEffectHandler::notImplementedTarget(const std::string_view effectName, const Target target)
    {
        throw NotImplementedError(
            "Not implemented: "s + effectName.data() + " with target "s + getTargetName(target).data()
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
                    ApiStatusCode::ILLEGAL_ARGUMENT,
                    "Effect '"s + effectName.data() + "' does not support parameter '" + kvPair.first + "'"
                );
            }
        }

        if (!eb.isClean())
        {
            throw MultipleErrors(eb.compileErrorMessage());
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
        const Target defaultValue
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
        auto it = params.find(HPAMOUNT_PERCENTAGE);
        if (it != params.end())
        {
            return {HPBasis::Percentage, std::stod(it->second)};
        }

        it = params.find(HPAMOUNT_ABSOLUTE);
        if (it != params.end())
        {
            return {HPBasis::Absolute, std::stod(it->second)};
        }

        throw InvalidUserInput(
            "Parameters for effect Drain contain neither "s + HPAMOUNT_PERCENTAGE + " nor " + HPAMOUNT_ABSOLUTE
        );
    }

    OptionProbabilityList AbstractEffectHandler::extractOptionProbabilities(const std::string_view effectName, const KeyValueMap& params)
    {
        EngineBase::ErrorBuffer eb;
        OptionProbabilityListBuilder pBuilder;

        for (const auto& entry : params)
        {
            try
            {
                const auto option     = std::stoi(entry.first);
                const auto percentage = std::stod(entry.second) / 100.0;
                pBuilder.addEntry(option, percentage);
            }
            catch (const std::invalid_argument&)
            {
                eb.append(
                    ApiStatusCode::INVALID_USER_INPUT,
                    std::format("Invalid option {} with value {}", entry.first, entry.second)
                );
            }
            catch (const std::out_of_range&)
            {
                eb.append(
                    ApiStatusCode::INVALID_USER_INPUT,
                    std::format("Invalid option {} with value {}", entry.first, entry.second)
                );
            }
        }

        if (!eb.isClean())
        {
            throw MultipleErrors(eb.compileErrorMessage());
        }

        return pBuilder.build();
    }

    double AbstractEffectHandler::extractSimpleNumber(const std::string_view effectName, const KeyValueMap& params)
    {

        if (params.size() != 1)
        {
            throw InvalidUserInput(std::format("{} takes exactly one parameter", effectName));
        }

        const auto& param = params.begin()->first;
        try
        {
            return std::stod(param);
        }
        catch (const std::invalid_argument&)
        {
            throw InvalidUserInput(std::format("Not a number: '{}'", param));
        }
        catch (const std::out_of_range&)
        {
            throw InvalidUserInput(std::format("Not a number: '{}'", param));
        }
    }

    EffectEvaluationTime AbstractEffectHandler::getEvaluationTime()
    {
        return EffectEvaluationTime::AfterRegularDamage;
    }
}
