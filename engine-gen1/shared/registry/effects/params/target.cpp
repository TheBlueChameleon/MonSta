#include <base/errors.hpp>

#include "target.hpp"

using namespace std::string_literals;

namespace MetaDefinition
{
    namespace EffectParams
    {
        Target getTargetFromName(const std::string_view name)
        {
            // *INDENT-OFF*
            if      (name == SELF)          { return Target::Self;        }
            else if (name == ENEMY)         { return Target::Enemy;       }
            else if (name == BOTH)          { return Target::Both;        }
            else if (name == LAST)          { return Target::Last;        }
            else if (name == CHOOSESELF)    { return Target::ChooseSelf;  }
            else if (name == CHOOSEENEMY)   { return Target::ChooseEnemy; }
            else if (name == RANDOMSELF)    { return Target::RandomSelf;  }
            else if (name == RANDOMENEMY)   { return Target::RandomEnemy; }
            else { throw  EngineError(ApiStatusCode::ILLEGAL_CLIENT_STATE, "Unknown Target: '"s + name.data() + "'");}
            // *INDENT-ON*
        }

        std::string_view getTargetName(const Target target)
        {
            switch (target)
            {
                case MetaDefinition::EffectParams::Target::Self:
                    return SELF;
                case MetaDefinition::EffectParams::Target::Enemy:
                    return ENEMY;
                case MetaDefinition::EffectParams::Target::Both:
                    return BOTH;
                case MetaDefinition::EffectParams::Target::Last:
                    return LAST;
                case MetaDefinition::EffectParams::Target::ChooseSelf:
                    return CHOOSESELF;
                case MetaDefinition::EffectParams::Target::ChooseEnemy:
                    return CHOOSEENEMY;
                case MetaDefinition::EffectParams::Target::RandomSelf:
                    return RANDOMSELF;
                case MetaDefinition::EffectParams::Target::RandomEnemy:
                    return RANDOMENEMY;
            }
            throw  EngineError(ApiStatusCode::ILLEGAL_CLIENT_STATE, "Unknown Target ID: "s + std::to_string(static_cast<int>(target)));
        }

    }   // namespace EffectParams
}       // namespace MetaDefinition
