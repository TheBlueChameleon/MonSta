#include <list>

#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"
#include "simulationmode/arena/pokemoninstance.hpp"

#include "drain.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    using namespace EffectParams;

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

        assertOnlySupportedParams(EFFECT_NAME, {TARGET, HP_PERCENTAGE, HP_ABSOLUTE}, params);
        const auto target = extractTarget(EFFECT_NAME, params, Target::Self);
        const auto amount = extractHPAmount(EFFECT_NAME, params);

        return Drain(amount, target);
    }

    void Drain::execute(
        SimulationMode::PokemonInstance& self,
        SimulationMode::PokemonInstance& enemy,
        SimulationMode::Scene& scene
    )
    {
        int recovered;
        switch (amount.basis)
        {
            case MetaDefinition::HPBasis::Absolute:
                recovered = amount.value < scene.lastDamageDone ? amount.value : scene.lastDamageDone;
                break;
            case MetaDefinition::HPBasis::Percentage:
                recovered = amount.value / 100.0 * scene.lastDamageDone;
                break;
        }

        switch (target)
        {
            case MetaDefinition::EffectParams::Target::Self:
                self.recoverHealth(recovered);
                break;
            case MetaDefinition::EffectParams::Target::Enemy:
                enemy.recoverHealth(recovered);
                break;
            case MetaDefinition::EffectParams::Target::Both:
                self.recoverHealth(recovered);
                enemy.recoverHealth(recovered);
                break;
            case MetaDefinition::EffectParams::Target::ChooseSelf:
            case MetaDefinition::EffectParams::Target::ChooseEnemy:
            case MetaDefinition::EffectParams::Target::RandomSelf:
            case MetaDefinition::EffectParams::Target::RandomEnemy:
                throw EngineError(
                    ApiStatusCode::ILLEGAL_CLIENT_STATE,
                    "Not implemented: Drain with target "s + getTargetName(target).data()
                );
                break;
        }
    }
} // namespace MetaDefinition
