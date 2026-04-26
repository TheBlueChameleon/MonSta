#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

namespace SimulationMode
{
    class PokemonInstance
    {
        public:
            PokemonInstance();

            void takeDamage(const int amount);
            void recoverHealth(const int amount);
    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
