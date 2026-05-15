#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "shared/registry/registry.hpp"

#include "simulationmode/arena/scene.hpp"

#include "accumulateandpayback.hpp"

using namespace SimulationMode;
using namespace std::string_literals;

namespace MetaDefinition
{
    namespace Effects
    {
        void AccumulateAndPayBack::dealDamage(PokemonInstance& self, PokemonInstance& enemy)
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

        AccumulateAndPayBack::AccumulateAndPayBack(const OptionProbabilityList& chargeTurnsProbabilities) :
            chargeTurnsProbabilities(chargeTurnsProbabilities)
        {}

        AccumulateAndPayBack AccumulateAndPayBack::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor, '|', ':');
            const auto chargeTurnsProbabilities = extractOptionProbabilities(EFFECT_NAME, params);
            return AccumulateAndPayBack(chargeTurnsProbabilities);
        }

        void AccumulateAndPayBack::execute(SimulationMode::Scene& scene)
        {
            auto& self = scene.getSelf();
            auto& enemy = scene.getEnemy();

            if (self.getSkipTurnCounter() == 0)
            {
                const int turns = chargeTurnsProbabilities.getRandomOption();
                self.setSkipTurnCounter(turns);
            }
            else
            {
                if (self.isLockedMoveReleaseTurn())
                {
                    dealDamage(self, enemy);
                }
                else
                {
                    self.addToAccumulatedDamage(self.getLastDamageReceived());
                }
            }
        }

    } // namespace Effects
} // namespace MetaDefinition
