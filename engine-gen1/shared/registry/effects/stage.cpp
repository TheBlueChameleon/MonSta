#include <base/errors.hpp>
#include <base/stringutils.hpp>

#include "simulationmode/arena/scene.hpp"
#include "simulationmode/arena/pokemoninstance.hpp"

#include "stage.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    using namespace EffectParams;

    namespace Effects
    {
        Stage::Stage(Target target, StatStage stat, int change) :
            target(target), stat(stat), change(change)
        {}

        std::pair<StatStage, int> Stage::extractStatStage(const AbstractEffectHandler::KeyValueMap& params)
        {
            const std::initializer_list<std::string_view> statNames =
            {
                STATSTAGE_ATK, STATSTAGE_DEF, STATSTAGE_SPC, STATSTAGE_SPD,
                STATSTAGE_ACCURACY, STATSTAGE_EVASION, STATSTAGE_CRITRATE
            };

            for (const auto statName : statNames)
            {
                const auto it = params.find(statName.data());
                if (it == params.end())
                {
                    continue;
                }
                else
                {
                    const auto statName = getStatStageFromName(it->first);
                    const auto statAmount = std::stoi(it->second);      // TODO: catch and rethrow as EngineError
                    return std::make_pair(statName, statAmount);
                }
            }

            missingParameter(EFFECT_NAME, statNames);
        }

        Stage Stage::buildEffect(const std::string_view parameterDescriptor)
        {
            const AbstractEffectHandler::KeyValueMap params = EngineBase::splitArgs(parameterDescriptor);

            assertOnlySupportedParams(EFFECT_NAME,
            {
                TARGET,
                STATSTAGE_ATK, STATSTAGE_DEF, STATSTAGE_SPC, STATSTAGE_SPD,
                STATSTAGE_ACCURACY, STATSTAGE_EVASION, STATSTAGE_CRITRATE
            },
            params);

            const auto target = extractTarget(EFFECT_NAME, params);
            const auto [stat, change] = extractStatStage(params);

            return Stage(target, stat, change);
        }

        void Stage::execute(
            SimulationMode::PokemonInstance& self,
            SimulationMode::PokemonInstance& enemy,
            SimulationMode::Scene& scene
        )
        {
            switch (target)
            {
                case MetaDefinition::EffectParams::Target::Self:
                    self.changeStatStage(stat, change);
                    break;
                case MetaDefinition::EffectParams::Target::Enemy:
                    enemy.changeStatStage(stat, change);
                    break;
                case MetaDefinition::EffectParams::Target::Both:
                    self.changeStatStage(stat, change);
                    enemy.changeStatStage(stat, change);
                    break;
                case MetaDefinition::EffectParams::Target::ChooseSelf:
                case MetaDefinition::EffectParams::Target::ChooseEnemy:
                case MetaDefinition::EffectParams::Target::RandomSelf:
                case MetaDefinition::EffectParams::Target::RandomEnemy:
                    notImplementedTarget(EFFECT_NAME, target);
            }
        }
    }   // namespace Effects
}       // namespace MetaDefinition
