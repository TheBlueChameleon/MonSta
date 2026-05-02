#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"

#include "multihit.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        MultiHit::MultiHit(const OptionProbabilityList& probabilities) :
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
            const auto last = target.getLastDamageReceived();
            for (int i = 0; i < turns-1; ++i)        // turns-1: first instance of damage has already been done.
            {
                if (target.getKnockedOutSubstitute())
                {
                    break;
                }
                target.takeDamage(last);
            }
        }


    } // namespace Effects
} // namespace MetaDefinition
