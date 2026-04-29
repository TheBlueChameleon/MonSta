#ifndef MATCHDEFINITION_HPP
#define MATCHDEFINITION_HPP

#include <filesystem>
#include <string>

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

    const std::string args;
};

#endif // MATCHDEFINITION_HPP
