#include "services/loggerservice.hpp"

#include "simulationmode/arena/scene.hpp"

#include "trap.hpp"

namespace MetaDefinition
{
    namespace Effects
    {

        Trap Trap::buildEffect(const std::string_view parameterDescriptor)
        {
            if (!parameterDescriptor.empty())
            {
                LoggerService::warnF(
                    "Encountered definition of effect '{}' with parameters '{}'. This effect does not take any parameters.",
                    EFFECT_NAME, parameterDescriptor
                );
            }

            return Trap();
        }

        void Trap::execute(SimulationMode::Scene& scene)
        {
            scene.getEnemy().setTrapped(true);
        }

    } // namespace Effects
} // namespace MetaDefinition
