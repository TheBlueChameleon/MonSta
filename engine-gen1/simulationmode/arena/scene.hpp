#ifndef SCENE_HPP
#define SCENE_HPP

#include "pokemoninstance.hpp"

namespace SimulationMode
{
    struct Scene
    {
        int lastDamageDone;

        bool stopProcessSecondaryEffects = false;
    };
}

#endif // SCENE_HPP
