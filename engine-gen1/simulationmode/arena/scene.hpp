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

            bool stopProcessSecondaryEffects = false;

            std::list<std::pair<MetaDefinition::Stat, int>> tempStatsSelf;
            std::list<std::pair<MetaDefinition::Stat, int>> tempStatsEnemy;

        public:
            PokemonInstance& getSelf();
            PokemonInstance& getEnemy();

            void setTemporaryStatSelf(const  MetaDefinition::Stat stat, const int value);
            void setTemporaryStatEnemy(const MetaDefinition::Stat stat, const int value);

            bool getStopProcessSecondaryEffects() const;
            void setStopProcessSecondaryEffects(bool value);

            void handleSeeds();
            void handleStatusDamage();

            void resetTempState();
            void flip();
            void nextTurn();
    };
}

#endif // SCENE_HPP
