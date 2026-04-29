#ifndef STAGE_H
#define STAGE_H

#include <string_view>

#include "params/target.hpp"
#include "params/statstage.hpp"

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        class Stage : AbstractEffectHandler
        {
            public:
                static constexpr auto EFFECT_NAME = "Stage";

            private:
                EffectParams::Target    target;
                EffectParams::StatStage stat;
                int                     change;

                static std::pair<EffectParams::StatStage, int> extractStatStage(const AbstractEffectHandler::KeyValueMap& params);

            public:
                Stage(
                    EffectParams::Target    target,
                    EffectParams::StatStage stat,
                    int                     change
                );

                static Stage buildEffect(const std::string_view parameterDescriptor);

                void execute(SimulationMode::Scene& scene);
        };
    }   // namespace Effects
}       // namespace MetaDefinition

#endif // STAGE_H
