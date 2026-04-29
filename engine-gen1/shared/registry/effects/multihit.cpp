#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"
#include "simulationmode/arena/pokemoninstance.hpp"

#include "multihit.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    using namespace EffectParams;

    namespace Effects
    {
        MultiHit::MultiHit(OptionProbabilityList probabilities) :
            probabilities(probabilities)
        {}

        MultiHit MultiHit::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor);
            OptionProbabilityListBuilder pBuilder;

            for (const auto& entry : params)
            {
                try
                {
                    const auto option     = std::stoi(entry.first);
                    const auto percentage = std::stod(entry.second) / 100.0;
                    pBuilder.addEntry(option, percentage);
                }
                catch (const std::invalid_argument& e)
                {
                    throw EngineError(
                        ApiStatusCode::INVALID_USER_INPUT,
                        "Not an integer: "s + entry.first
                    );
                }
                catch (const std::out_of_range& e)
                {
                    throw EngineError(
                        ApiStatusCode::INVALID_USER_INPUT,
                        "Not an percentage: "s + entry.first
                    );
                }
            }

            const auto probabilities = pBuilder.build();
            return MultiHit(probabilities);
        }

        void MultiHit::execute(SimulationMode::Scene& scene)
        {
            const auto turns = probabilities.getRandomOption();
            for (int i = 0; i < turns-1; ++i)        // turns-1: first instance of damage has already been done.
            {
                scene.damageEnemy(scene.getLastDamageDone());
            }
        }


    } // namespace Effects
} // namespace MetaDefinition
