#ifndef MATCHDEFINITION_H
#define MATCHDEFINITION_H

#include <filesystem>

struct MatchDefinition
{
    const std::filesystem::path mechanics;

    const std::filesystem::path player1Team;
    const std::filesystem::path player1Strategy;

    const std::filesystem::path player2Team;
    const std::filesystem::path player2Strategy;

    const std::filesystem::path pkmnDefs;
    const std::filesystem::path moveDefs;
    const std::filesystem::path typeDefs;
    const std::filesystem::path itemDefs;
};

#endif // MATCHDEFINITION_H
