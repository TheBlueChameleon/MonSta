#include <format>
#include <string>
#include <sstream>

#include <runmodes/ITemplatesDefinition.hpp>

#include <services/fileservice.hpp>

#include "shared/registry/typechart.hpp"
#include "shared/registry/moves/move.hpp"

#include "allowedvalueswriter.hpp"
#include "templatesmode.hpp"

using namespace Registry;
using namespace MetaDefinition;

namespace TemplateMode
{
    static constexpr auto HEADLINE = "{} ({})";
    static constexpr char HEADLINE_1 = '=';
    static constexpr char HEADLINE_2 = '-';
    static constexpr char HEADLINE_3 = 39;      // = apostrophe
    static constexpr auto END = "\n\n";

    static std::string makeUnderlinedText(
        const std::string_view text,
        const char underlineChar
    )
    {
        return std::format("{}\n"
                           "{}\n",
                           text,
                           std::string(text.length(), underlineChar)
                          );
    }

    static std::string makeHeadline(
        const std::string_view text,
        const std::string_view defaultFileName,
        const char underlineChar
    )
    {
        return makeUnderlinedText(
                   std::format(HEADLINE, text, defaultFileName),
                   underlineChar
               );
    }

    static std::string makeTypeDefs()
    {
        constexpr auto INTRO = R"(
This file contains the type effectiveness chart and the attack status associated with each type.
The following columns must be present:
 - '{}'
 - '{}'
)";
        constexpr auto COLUMN_ATTACK = R"(
The column '{}' may contain arbitrary strings that will be interpreted as Pokemon types.
Each value in this column must also appear as a column header, in addition to the two aforementioned headers.
)";
        constexpr auto COLUMN_CATEGORY = R"(
The column '{}' defines which stats will be used to compute the damage done by moves of the associated type.
It may be either of these values:
 - '{}'
 - '{}'
)";

        return std::format(
            "{}"
            "{}"
            "{}"
            "{}"
            "{}",
            makeHeadline("Type Definition File", TYPE_DEFINITION_FILE, HEADLINE_1),
            std::format(INTRO, TypeChart::ATTACKER, TypeChart::CATEGORY),
            std::format(COLUMN_ATTACK, TypeChart::ATTACKER),
            std::format(COLUMN_CATEGORY, TypeChart::CATEGORY, MetaDefinition::PHYSICAL, MetaDefinition::SPECIAL),
            END
            );
    }

    static std::string makeMoveDefs() {
        constexpr auto INTRO = R"(
This file contains all moves together with their primary and secondary effects.
The following columns must be present:
 - '{}'
 - '{}'
 - '{}'
 - '{}'
 - '{}'
 - '{}'
 - '{}'
 - '{}'
)";
        constexpr auto TYPESPEC = R"(
'{}' may be any type defined in the type definition file.
)";
        constexpr auto EFFECTSPEC = R"(
'{}' may be any descriptor as specified in section Effects.
)";

        return std::format(
            "{}"
            "{}"
            "{}"
            "{}"
            "{}",
            makeHeadline("Move Definition File", MOVE_DEFINITION_FILE, HEADLINE_1),
            std::format(INTRO, Move::NAME, Move::TYPE, Move::PP, Move::POWER, Move::ACCURACY, Move::PRIORITY, Move::EFFECT, Move::EFFECT_CHANCE),
            std::format(TYPESPEC, Move::TYPE),
            std::format(EFFECTSPEC, Move::EFFECT),
            END
        );
    }

    static std::string makeEffectsList()
    {
        constexpr auto INTRO = R"(
Effects describe simulation aspects that are not covered by the standard move mechanism.
They are used both, for secondary effects of moves (e.g. cause paralysis) and for effects of items (e.g. heal fixed amount of HP).

Any move or item may have zero to multiple effects. The individual effects are given as a semicolon separated list, i.e. in the following form:
  EFFECT1; EFFECT2; EFFECT3; ...
Any whitespaces in the list are ignored.

Effects are grouped into similar categories (e.g. cause some status condition).
The specific form of the effect (e.g. cause paralysis) is given as a parameter to the effect.
Effect-name and effect-parameter are separated with an equals sign.
That is, a list of effects may look like the following:
  EFFECT1 = PARAMETERS1; EFFECT2 = PARAMETERS2; EFFECT3 = PARAMETERS3; ...
Whitespaces before and after the equals sign will be ignored.

Some parameters are themselves key-value-pairs.
(E.g.: status moves may target the enemy or the own active pokemon. This information is given by the key 'Target' and the value of either 'Enemy' or 'Self').
Such parameters are a bar-separated list, in which key and value are associated by a colon.
That is, they may look like the following:
  EFFECT = KEY1 : VALUE1 | KEY2 : VALUE2 | ...
Any whitespaces in the list are ignored.

Note that the order of effects is relevant; they are executed in the order they are specified in the corresponding files.
)";

        constexpr auto FOO = R"(
The following effects names are allowed:
 - 'TBD'
)";

        return std::format(
                   "{}"
                   "{}"
                   "{}"
                   "{}",
                   makeUnderlinedText("Effects", HEADLINE_1),
                   INTRO,
                   FOO,
                   END
               );
    }

    void writeAllowedValueFile(const std::filesystem::path& target)
    {
        const auto INTRO = "This file explains some of the requirements for the contents of the CSV files used to configure a simulation.\n"
                           "For details, see the Simulation Engine Documentation\n"
                           "\n\n";

        const auto typeDefsText = makeTypeDefs();
        const auto moveDefsText = makeMoveDefs();
        const auto effectsList = makeEffectsList();

        const auto fullText = std::format(
                                  "{}"
                                  "{}"
                                  "{}"
                                  "{}",
                                  INTRO,
                                  typeDefsText,
                                  moveDefsText,
                                  effectsList
                              );
        FileService::write(target, fullText);

    }

} // namespace TemplateMode
