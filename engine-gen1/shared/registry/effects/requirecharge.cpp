#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"

#include "requirecharge.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        RequireCharge::RequireCharge(const OptionProbabilityList& chargeTurnsProbabilities) :
            chargeTurnsProbabilities(chargeTurnsProbabilities)
        {}

        RequireCharge RequireCharge::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor, '|', ':');
            const auto probabilities = extractOptionProbabilities(EFFECT_NAME, params);
            return RequireCharge(probabilities);
        }

        EffectEvaluationTime RequireCharge::getEvaluationTime()
        {
            return EffectEvaluationTime::BeforeRegularDamage;
        }

        void RequireCharge::execute(SimulationMode::Scene& scene)
        {
            auto& self = scene.getSelf();
            const int turns = chargeTurnsProbabilities.getRandomOption();
            self.setSkipTurnCounter(turns);
            self.lockMove(self.getSelectedMove(), turns + 1);
        }

    } // namespace Effects
} // namespace MetaDefinition
