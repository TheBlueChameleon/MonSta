#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>

#include "shared/defs/stat.hpp"

#include "pokemoninstance.hpp"

namespace SimulationMode
{
    class Scene
    {
        private:
            PokemonInstance* self;
            PokemonInstance* enemy;

            int  lastDamageDone;
            bool stopProcessSecondaryEffects = false;

            std::list<std::pair<MetaDefinition::Stat, int>> tempStatsSelf;
            std::list<std::pair<MetaDefinition::Stat, int>> tempStatsEnemy;

        public:
            PokemonInstance& getSelf();
            PokemonInstance& getEnemy();

            void damageSelf(const int amount);
            void damageEnemy(const int amount);

            void healSelf(const int amount);
            void healEnemy(const int amount);

            void setTemporaryStatSelf(const  MetaDefinition::Stat stat, const int value);
            void setTemporaryStatEnemy(const MetaDefinition::Stat stat, const int value);

            int  getLastDamageDone() const;
            void setLastDamageDone(int value);

            bool getStopProcessSecondaryEffects() const;
            void setStopProcessSecondaryEffects(bool value);

            void resetTempState();
            void flip();
    };
}

#endif // SCENE_HPP
