#include <list>

#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"
#include "simulationmode/arena/pokemoninstance.hpp"

#include "drain.hpp"

namespace MetaDefinition
{
    Drain::Drain(const NumberInterpretation basis, const double value) :
        basis(basis),
        value(value)
    {}

    Drain Drain::buildEffect(const std::string_view parameterDescriptor)
    {
        const auto params = EngineBase::splitArgsOrdered(parameterDescriptor);

        if (params.size() != 1)
        {
            throw EngineError(
                ApiStatusCode::INVALID_USER_INPUT,
                "Effect Drain needs exactly one parameter"
            );
        }

        const auto& parameter = params.front();
        const auto basis = getNumberInterpretationFromName(parameter.first);
        const auto value = std::stod(parameter.second);

        return Drain(basis, value);
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
