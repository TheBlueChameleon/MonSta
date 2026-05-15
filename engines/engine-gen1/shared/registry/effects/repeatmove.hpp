#ifndef REPEATMOVE_HPP
#define REPEATMOVE_HPP

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        class RepeatMove : public AbstractEffectHandler
        {
            public:
                static constexpr auto EFFECT_NAME = "RepeatMove";

            private:
                const OptionProbabilityList repeatProbabilities;

            public:
                RepeatMove(const OptionProbabilityList& repeatProbabilities);

                static RepeatMove buildEffect(const std::string_view parameterDescriptor);

                void execute(SimulationMode::Scene& scene);
        };

    } // namespace Effects
} // namespace MetaDefinition

#endif // REPEATMOVE_HPP
