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
            if      (name == TARGET_SELF)          { return Target::Self;        }
            else if (name == TARGET_ENEMY)         { return Target::Enemy;       }
            else if (name == TARGET_BOTH)          { return Target::Both;        }
            else if (name == TARGET_CHOOSESELF)    { return Target::ChooseSelf;  }
            else if (name == TARGET_CHOOSEENEMY)   { return Target::ChooseEnemy; }
            else if (name == TARGET_RANDOMSELF)    { return Target::RandomSelf;  }
            else if (name == TARGET_RANDOMENEMY)   { return Target::RandomEnemy; }
            else { throw  IllegalArgumentError("Unknown Target: '"s + name.data() + "'");}
            // *INDENT-ON*
        }

        std::string_view getTargetName(const Target target)
        {
            switch (target)
            {
                case MetaDefinition::EffectParams::Target::Self:
                    return TARGET_SELF;
                case MetaDefinition::EffectParams::Target::Enemy:
                    return TARGET_ENEMY;
                case MetaDefinition::EffectParams::Target::Both:
                    return TARGET_BOTH;
                case MetaDefinition::EffectParams::Target::ChooseSelf:
                    return TARGET_CHOOSESELF;
                case MetaDefinition::EffectParams::Target::ChooseEnemy:
                    return TARGET_CHOOSEENEMY;
                case MetaDefinition::EffectParams::Target::RandomSelf:
                    return TARGET_RANDOMSELF;
                case MetaDefinition::EffectParams::Target::RandomEnemy:
                    return TARGET_RANDOMENEMY;
            }
            throw  IllegalArgumentError("Unknown Target ID: "s + std::to_string(static_cast<int>(target)));
        }

    }   // namespace EffectParams
}       // namespace MetaDefinition
