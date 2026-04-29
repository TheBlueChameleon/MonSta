#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"
#include "simulationmode/arena/pokemoninstance.hpp"

#include "drain.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    using namespace EffectParams;

    namespace Effects
    {
        Drain::Drain(
            const EffectParams::HPAmount amount,
            const Target target
        ) :
            amount(amount),
            target(target)
        {}

        Drain Drain::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor);

            assertOnlySupportedParams(EFFECT_NAME, {TARGET, HPAMOUNT_PERCENTAGE, HPAMOUNT_ABSOLUTE}, params);
            const auto target = extractTarget(EFFECT_NAME, params, Target::Self);
            const auto amount = extractHPAmount(EFFECT_NAME, params);

            return Drain(amount, target);
        }

        void Drain::execute(SimulationMode::Scene& scene)
        {
            int recovered;
            switch (amount.basis)
            {
                case MetaDefinition::HPBasis::Absolute:
                    recovered = amount.value < scene.getLastDamageDone() ? amount.value : scene.getLastDamageDone();
                    break;
                case MetaDefinition::HPBasis::Percentage:
                    recovered = amount.value / 100.0 * scene.getLastDamageDone();
                    break;
            }

            switch (target)
            {
                case MetaDefinition::EffectParams::Target::Self:
                    scene.getSelf().recoverHealth(recovered);
                    break;
                case MetaDefinition::EffectParams::Target::Enemy:
                    scene.getEnemy().recoverHealth(recovered);
                    break;
                case MetaDefinition::EffectParams::Target::Both:
                    scene.getSelf().recoverHealth(recovered);
                    scene.getEnemy().recoverHealth(recovered);
                    break;
                case MetaDefinition::EffectParams::Target::ChooseSelf:
                case MetaDefinition::EffectParams::Target::ChooseEnemy:
                case MetaDefinition::EffectParams::Target::RandomSelf:
                case MetaDefinition::EffectParams::Target::RandomEnemy:
                    notImplementedTarget(EFFECT_NAME, target);
            }
        }

    }   // namespace Effects
}       // namespace MetaDefinition
