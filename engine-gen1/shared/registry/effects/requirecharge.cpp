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
            const int turns = chargeTurnsProbabilities.getRandomOption();
            auto& self = scene.getSelf();
            if (self.getSkipTurnCount() == 0)
            {
                self.setSkipTurnCount(turns);
                if (self.getLockedMove() != nullptr)
                {
                    self.lockMove(self.getCurrentMove(), turns + 1);
                }
            }
        }

    } // namespace Effects
} // namespace MetaDefinition
