#ifndef SCENE_HPP
#define SCENE_HPP

#include "pokemoninstance.hpp"

namespace SimulationMode
{
    class Scene
    {
        private:
            PokemonInstance* self;
            PokemonInstance* enemy;

            int lastDamageDone;
            bool stopProcessSecondaryEffects = false;

        public:
            PokemonInstance& getSelf();
            PokemonInstance& getEnemy();

            int getLastDamageDone() const;
            void setLastDamageDone(int value);

            bool getStopProcessSecondaryEffects() const;
            void setStopProcessSecondaryEffects(bool value);

            void flip();
    };
}

#endif // SCENE_HPP
