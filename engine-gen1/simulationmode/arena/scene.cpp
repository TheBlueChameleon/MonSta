#include "scene.hpp"

namespace SimulationMode
{
    void Scene::flip()
    {
        std::swap(self, enemy);
    }

    bool Scene::getStopProcessSecondaryEffects() const
    {
        return stopProcessSecondaryEffects;
    }

    void Scene::setStopProcessSecondaryEffects(bool value)
    {
        stopProcessSecondaryEffects = value;
    }

    int Scene::getLastDamageDone() const
    {
        return lastDamageDone;
    }

    void Scene::setLastDamageDone(int value)
    {
        lastDamageDone = value;
    }

}
