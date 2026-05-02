#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"

#include "drain.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    namespace Effects
    {
        Drain::Drain(
            const HPAmount amount,
            const Target target
        ) :
            amount(amount),
            target(target)
        {}

        Drain Drain::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor, '|', ':');

            assertOnlySupportedParams(EFFECT_NAME, {TARGET, HPAMOUNT_PERCENTAGE, HPAMOUNT_ABSOLUTE}, params);
            const auto target = extractTarget(EFFECT_NAME, params, Target::Self);
            const auto amount = extractHPAmount(EFFECT_NAME, params);

            return Drain(amount, target);
        }

        static void computeAndHealDamage(SimulationMode::PokemonInstance& targetMon, const HPAmount amount)
        {
            // TODO: tie this to mechanics flag?
            if (targetMon.getKnockedOutSubstitute())
            {
                return;
            }

            int recoveredHP;
            switch (amount.basis)
            {
                case MetaDefinition::HPBasis::Absolute:
                    recoveredHP = amount.value < targetMon.getLastDamageReceived() ?
                                  amount.value :
                                  targetMon.getLastDamageReceived();
                    break;
                case MetaDefinition::HPBasis::Percentage:
                    recoveredHP = amount.value / 100.0 * targetMon.getLastDamageReceived();
                    break;
            }

            targetMon.recoverHealth(std::min(1, recoveredHP));
        }

        void Drain::execute(SimulationMode::Scene& scene)
        {
            switch (target)
            {
                case MetaDefinition::Target::Self:
                    computeAndHealDamage(scene.getSelf(), amount);
                    break;
                case MetaDefinition::Target::Enemy:
                    computeAndHealDamage(scene.getEnemy(), amount);
                    break;
                case MetaDefinition::Target::Both:
                    computeAndHealDamage(scene.getSelf(), amount);
                    computeAndHealDamage(scene.getEnemy(), amount);
                    break;
                case MetaDefinition::Target::ChooseSelf:
                case MetaDefinition::Target::ChooseEnemy:
                case MetaDefinition::Target::RandomSelf:
                case MetaDefinition::Target::RandomEnemy:
                    notImplementedTarget(EFFECT_NAME, target);
            }
        }

    }   // namespace Effects
}       // namespace MetaDefinition
