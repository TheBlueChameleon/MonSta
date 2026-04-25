#include <format>
#include <string>

#include <services/fileservice.hpp>
#include <services/jsonservice.hpp>

#include "shared/schemavalidationconstants.hpp"

#include "jsontemplateswriter.hpp"

using namespace std::string_literals;

namespace TemplateMode
{
    static const auto UNDEFINED = "<to be defined>";

    static std::string quote(const std::string_view quotee)
    {
        return std::format(R"("{}")", quotee);
    }

    const std::string_view writeMechanicsDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto tagName = SchemaValidation::jtag_base + defaultName.data();
        const auto handle = JsonService::parseValidatePatchAndAdd(
                                IJsonServiceTypes::JsonTag(tagName.data()),
                                "{}",
                                SchemaValidation::JTAG_MECHANICSDEFINITION
                            );
        auto memBlock = JsonService::dump(handle);

        FileService::write(defaultName, memBlock.getAsStringView());

        return defaultName;
    }

    const std::string_view writeTeamDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName,
        const std::string_view playerType
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto tagName = SchemaValidation::jtag_base + defaultName.data();
        const auto explicitFields = "{"s +
                                    quote(playerType) + " : " + "{" + quote(SchemaValidation::JKEY_PLAYER_NAME) + " : " + quote(UNDEFINED) + "}," +
                                    quote(SchemaValidation::JKEY_POKEMON) + ": [{" +
                                    quote(SchemaValidation::JKEY_POKEMON_SPECIES) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_LEVEL) + " : 5," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK1) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK2) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK3) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK4) + " : " + quote(UNDEFINED) +
                                    "}]" +
                                    "}";

        const auto handle = JsonService::parseValidatePatchAndAdd(
                                IJsonServiceTypes::JsonTag(tagName.data()),
                                explicitFields,
                                SchemaValidation::JTAG_TEAMDEFINITION
                            );
        auto memBlock = JsonService::dump(handle);

        FileService::write(defaultName, memBlock.getAsStringView());

        return defaultName;
    }

    void writeSchemas()
    {
        auto handleTeamDef = JsonService::get(SchemaValidation::JTAG_TEAMDEFINITION);
        auto contentTeamDef = JsonService::dump(handleTeamDef);
        FileService::write(SchemaValidation::filename_teamDefinitionSchema, contentTeamDef.getAsStringView());

        auto handleMechanicsDef = JsonService::get(SchemaValidation::JTAG_MECHANICSDEFINITION);
        auto contentMechanicsDef = JsonService::dump(handleMechanicsDef);
        FileService::write(SchemaValidation::filename_mechanicsDefinitionSchema, contentMechanicsDef.getAsStringView());
    }

} // namespace TemplateMode
