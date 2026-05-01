#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"

#include "multihit.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    namespace Effects
    {
        MultiHit::MultiHit(OptionProbabilityList probabilities) :
            hitCountProbabilities(probabilities)
        {}

        MultiHit MultiHit::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor, '|', ':');
            const auto probabilities = extractOptionProbabilities(EFFECT_NAME, params);
            return MultiHit(probabilities);
        }

        void MultiHit::execute(SimulationMode::Scene& scene)
        {
            auto& target = scene.getEnemy();
            const auto turns = hitCountProbabilities.getRandomOption();
            for (int i = 0; i < turns-1; ++i)        // turns-1: first instance of damage has already been done.
            {
                auto last = target.getLastDamageReceived();
                if (last == SimulationMode::PokemonInstance::DELEGATE_BROKEN)
                {
                    break;
                }
                target.takeDamage(last);
            }
        }


    } // namespace Effects
} // namespace MetaDefinition
