#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "shared/registry/registry.hpp"

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
            auto& enemy = scene.getEnemy();

            if (self.getSkipTurnCounter() > 0)
            {
                self.addToAccumulatedDamage(self.getLastDamageReceived());
            }
            else
            {
                const auto damage = self.getAccumulatedDamage() * paybackMultiplyer;
                self.resetAccumulatedDamage();
                if (enemy.isSemiInvulnerable())
                {
                    if (Registry::mechanicsDefinition.bideGlitch)
                    {
                        enemy.takeDamage(damage);
                    }
                }
                else
                {
                    enemy.takeDamage(damage);
                }
            }
        }

    } // namespace Effects
} // namespace MetaDefinition
