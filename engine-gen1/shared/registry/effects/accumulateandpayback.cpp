#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"

#include "accumulateandpayback.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    namespace Effects
    {
        AccumulateAndPayBack::AccumulateAndPayBack(const double paybackMultiplier) :
            paybackMultiplyer(paybackMultiplier)
        {}

        AccumulateAndPayBack AccumulateAndPayBack::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor, '|', ':');
            const double multiplier = extractSimpleNumber(EFFECT_NAME, params);
            return AccumulateAndPayBack(multiplier);
        }

        void AccumulateAndPayBack::execute(SimulationMode::Scene& scene)
        {
            auto& self = scene.getSelf();

            if (self.getSkipTurnCount() > 0)
            {

            }
            else
            {
                scene.damageEnemy(self.getAccumulatedDamage() * paybackMultiplyer);
            }
        }

    } // namespace Effects
} // namespace MetaDefinition
