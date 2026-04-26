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
        const NumberInterpretation basis,
        const double value,
        const Target target
    ) :
        basis(basis),
        value(value),
        target(target)
    {}

    Drain Drain::buildEffect(const std::string_view parameterDescriptor)
    {
        const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor);

        assertOnlySupportedParams({TARGET, PERCENTAGE, ABSOLUTE}, params);
        const auto target = extractTarget(params, Target::Self);
        const auto [basis, value] = extractEffectStrength(params);

        return Drain(basis, value, target);
    }

    bool Drain::execute(SimulationMode::PokemonInstance& self,
                        SimulationMode::PokemonInstance& enemy,
                        SimulationMode::Scene& scene
                       )
    {
        int amount;
        switch (basis)
        {
            case MetaDefinition::NumberInterpretation::Absolute:
                amount = value < scene.lastDamageDone ? value : scene.lastDamageDone;
                break;
            case MetaDefinition::NumberInterpretation::Percentage:
                amount = value / 100.0 * scene.lastDamageDone;
                break;
        }

        self.recoverHealth(amount);

        return true;
    }
} // namespace MetaDefinition
