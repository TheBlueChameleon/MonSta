#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"

#include "repeatmove.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        RepeatMove::RepeatMove(const OptionProbabilityList& repeatProbabilities) :
            repeatProbabilities(repeatProbabilities)
        {}

        RepeatMove RepeatMove::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor, '|', ':');
            const auto probabilities = extractOptionProbabilities(EFFECT_NAME, params);
            return RepeatMove(probabilities);
        }

        void RepeatMove::execute(SimulationMode::Scene& scene)
        {
            const auto turns = repeatProbabilities.getRandomOption();
            auto& self = scene.getSelf();
            self.lockNextMove(self.getCurrentMove(), turns);
        }

    } // namespace Effects
} // namespace MetaDefinition
