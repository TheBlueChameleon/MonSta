#include <base/stringutils.hpp>

#include "services/loggerservice.hpp"
#include "services/rngservice.hpp"

#include "simulationmode/arena/scene.hpp"

#include "trap.hpp"

namespace MetaDefinition
{
    namespace Effects
    {

        Trap::Trap(const OptionProbabilityList& hitCountProbabilities) :
            hitCountProbabilities(hitCountProbabilities)
        {}

        Trap Trap::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor, '|', ':');
            const auto probabilities = extractOptionProbabilities(EFFECT_NAME, params);
            return Trap(probabilities);
        }

        void Trap::execute(SimulationMode::Scene& scene)
        {
            auto& self = scene.getSelf();
            auto& enemy = scene.getEnemy();

            const int turns = hitCountProbabilities.getRandomOption();
            enemy.addVolatileStatus(VolatileStatusCondition::BOUND, 1);
            self.lockMove(self.getCurrentMove(), turns);
        }

    } // namespace Effects
} // namespace MetaDefinition
