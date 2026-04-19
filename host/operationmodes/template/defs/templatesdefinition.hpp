#ifndef TEMPLATESDEFINITION_H
#define TEMPLATESDEFINITION_H

#include <string>
#include <filesystem>

struct TemplatesDefinition
{
    const std::filesystem::path mechanicsDefinition;
    const std::filesystem::path player1Team;
    const std::filesystem::path player1Strategy;
    const std::filesystem::path player2Team;
    const std::filesystem::path player2Strategy;
    const std::filesystem::path pkmnDefs;
    const std::filesystem::path moveDefs;
    const std::filesystem::path typeDefs;
    const std::filesystem::path itemDefs;

    const bool writeSchemas;
    const bool writeAllowedValues;

    const std::string args;
};

#endif // TEMPLATESDEFINITION_H
