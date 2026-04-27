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
            virtual void execute(
                SimulationMode::PokemonInstance& self,
                SimulationMode::PokemonInstance& enemy,
                SimulationMode::Scene& scene
            ) = 0;
    };

} // namespace SimulationMode

#endif // ABSTRACTEFFECTHANDLER_HPP
