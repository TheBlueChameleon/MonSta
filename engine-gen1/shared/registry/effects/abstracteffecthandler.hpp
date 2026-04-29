#ifndef ABSTRACTEFFECTHANDLER_HPP
#define ABSTRACTEFFECTHANDLER_HPP

#include <set>
#include <string>
#include <unordered_map>

#include "params/target.hpp"
#include "params/hpamount.hpp"

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
                const EffectParams::Target target
            );

        public:
            static void assertOnlySupportedParams(
                const std::string_view effectName,
                const KeySet& supportedParamKeys,
                const KeyValueMap& actualParams
            );

            static EffectParams::Target extractTarget(
                const std::string_view effectName,
                const KeyValueMap& params
            );
            static EffectParams::Target extractTarget(
                const std::string_view effectName,
                const KeyValueMap& params,
                const EffectParams::Target defaultValue
            );

            static EffectParams::HPAmount extractHPAmount(
                const std::string_view effectName,
                const KeyValueMap& params
            );

        public:
            virtual void execute(SimulationMode::Scene& scene) = 0;
            virtual constexpr EffectEvaluationTime getEvaluationTime();
    };

} // namespace SimulationMode

#endif // ABSTRACTEFFECTHANDLER_HPP
