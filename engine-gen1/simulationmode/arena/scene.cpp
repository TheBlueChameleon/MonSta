#include "scene.hpp"

namespace SimulationMode
{
    void Scene::damageSelf(const int amount)
    {
        self->takeDamage(amount);
    }

    void Scene::damageEnemy(const int amount)
    {
        enemy->takeDamage(amount);
    }

    void Scene::healSelf(const int amount)
    {
        self->recoverHealth(amount);
    }

    void Scene::healEnemy(const int amount)
    {
        enemy->recoverHealth(amount);
    }

    void Scene::setTemporaryStatSelf(const MetaDefinition::Stat stat, const int value)
    {
        const int old = self->getStat(stat);
        self->setStat(stat, value);
        tempStatsSelf.push_back(std::make_pair(stat, old));
    }

    void Scene::setTemporaryStatEnemy(const MetaDefinition::Stat stat, const int value)
    {
        const int old = self->getStat(stat);
        enemy->setStat(stat, value);
        tempStatsEnemy.push_back(std::make_pair(stat, old));
    }

    bool Scene::getStopProcessSecondaryEffects() const
    {
        return stopProcessSecondaryEffects;
    }

    void Scene::setStopProcessSecondaryEffects(bool value)
    {
        stopProcessSecondaryEffects = value;
    }

    void Scene::resetTempState()
    {
        stopProcessSecondaryEffects = false;

        for (const auto tempStat : tempStatsSelf)
        {
            self->setStat(tempStat.first, tempStat.second);
        }
        tempStatsSelf.clear();
        for (const auto tempStat : tempStatsEnemy)
        {
            enemy->setStat(tempStat.first, tempStat.second);
        }
        tempStatsEnemy.clear();
    }

    void Scene::flip()
    {
        std::swap(self, enemy);
    }

}
