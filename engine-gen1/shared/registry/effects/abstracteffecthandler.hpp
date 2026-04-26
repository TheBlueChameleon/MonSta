#ifndef ABSTRACTEFFECTHANDLER_HPP
#define ABSTRACTEFFECTHANDLER_HPP

namespace SimulationMode
{
    class PokemonInstance;
    class Scene;
}

namespace MetaDefinition
{
    struct AbstractEffectHandler
    {
        virtual bool execute(SimulationMode::PokemonInstance& self,
                             SimulationMode::PokemonInstance& enemy,
                             SimulationMode::Scene& scene) = 0;
    };

} // namespace SimulationMode

#endif // ABSTRACTEFFECTHANDLER_HPP
