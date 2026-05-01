#ifndef ABSTRACTEFFECTHANDLER_HPP
#define ABSTRACTEFFECTHANDLER_HPP

#include <set>
#include <string>
#include <unordered_map>

#include "shared/defs/hpamount.hpp"
#include "shared/defs/optionprobabilitylist.hpp"
#include "shared/defs/target.hpp"

namespace EngineBase
{
    class ErrorBuffer;
}

namespace SimulationMode
{
    class PokemonInstance;
    class Scene;
}

namespace MetaDefinition
{
    enum class EffectEvaluationTime {BeforeRegularDamage, AfterRegularDamage};

    class AbstractEffectHandler
    {
        public:
            using KeySet      = std::set<std::string>;
            using KeyValueMap = std::unordered_map<std::string, std::string>;

        protected:
            [[noreturn]] static void missingParameter(
                const std::string_view effectName,
                const std::string_view paramName
            );
            [[noreturn]] static void missingParameter(
                const std::string_view effectName,
                const std::initializer_list<std::string_view> paramNames
            );

            [[noreturn]] static void notImplementedTarget(
                const std::string_view effectName,
                const Target target
            );

        public:
            static void assertOnlySupportedParams(
                const std::string_view effectName,
                const KeySet& supportedParamKeys,
                const KeyValueMap& actualParams
            );

            static Target extractTarget(
                const std::string_view effectName,
                const KeyValueMap& params
            );
            static Target extractTarget(
                const std::string_view effectName,
                const KeyValueMap& params,
                const Target defaultValue
            );

            static HPAmount extractHPAmount(
                const std::string_view effectName,
                const KeyValueMap& params
            );

            static OptionProbabilityList extractOptionProbabilities(
                const std::string_view effectName,
                const KeyValueMap& params
            );

        public:
            virtual void execute(SimulationMode::Scene& scene) = 0;
            virtual EffectEvaluationTime getEvaluationTime();
    };

} // namespace SimulationMode

#endif // ABSTRACTEFFECTHANDLER_HPP
