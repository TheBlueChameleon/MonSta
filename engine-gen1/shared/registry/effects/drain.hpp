#ifndef DRAIN_H
#define DRAIN_H

#include <string_view>

#include "abstracteffecthandler.hpp"
#include "numberinterpretation.hpp"

namespace MetaDefinition
{
    class Drain : public AbstractEffectHandler
    {
        private:
            const NumberInterpretation basis;
            const double value;

        public:
            Drain(const NumberInterpretation basis, const double value);
            static Drain buildEffect(const std::string_view parameterDescriptor);

            bool execute(
                SimulationMode::PokemonInstance& self,
                SimulationMode::PokemonInstance& enemy,
                SimulationMode::Scene& scene
            );
    };

} // namespace MetaDefinition

#endif // DRAIN_H
