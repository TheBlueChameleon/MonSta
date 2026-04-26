#ifndef ABSTRACTEFFECTHANDLER_HPP
#define ABSTRACTEFFECTHANDLER_HPP

#include <set>
#include <string>
#include <unordered_map>

#include "params/target.hpp"
#include "params/numberinterpretation.hpp"

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

            virtual bool execute(SimulationMode::PokemonInstance& self,
                                 SimulationMode::PokemonInstance& enemy,
                                 SimulationMode::Scene& scene) = 0;

            static void assertOnlySupportedParams(
                const KeySet& supportedParamKeys,
                const KeyValueMap& actualParams
            );

            static EffectParams::Target extractTarget(const KeyValueMap& params, const EffectParams::Target defaultValue);
            static std::pair<EffectParams::NumberInterpretation, double> extractEffectStrength(const KeyValueMap& params);
    };

} // namespace SimulationMode

#endif // ABSTRACTEFFECTHANDLER_HPP
