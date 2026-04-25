#ifndef ABSTRACTEFFECTHANDLER_HPP
#define ABSTRACTEFFECTHANDLER_HPP

namespace SimulationMode
{
    class PokemonInstance;
    class Scene;

    struct AbstractEffectHandler
    {
        virtual bool execute(PokemonInstance& self, PokemonInstance& enemy, Scene& scene) = 0;
    };

} // namespace SimulationMode

#endif // ABSTRACTEFFECTHANDLER_HPP
