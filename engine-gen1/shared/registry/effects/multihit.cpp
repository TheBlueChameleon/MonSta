#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"
#include "simulationmode/arena/pokemoninstance.hpp"

#include "multihit.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    namespace Effects
    {
        MultiHit::MultiHit(OptionProbabilityList probabilities) :
            probabilities(probabilities)
        {}

        MultiHit MultiHit::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor);
            const auto probabilities = extractOptionProbabilities(EFFECT_NAME, params);
            return MultiHit(probabilities);
        }

        void MultiHit::execute(SimulationMode::Scene& scene)
        {
            const auto turns = probabilities.getRandomOption();
            for (int i = 0; i < turns-1; ++i)        // turns-1: first instance of damage has already been done.
            {
                scene.damageEnemy(scene.getLastDamageDone());
            }
        }


    } // namespace Effects
} // namespace MetaDefinition
