#ifndef IMATCHDEFINITION_HPP
#define IMATCHDEFINITION_HPP

struct IMatchDefinition
{
    const char* const mechanics;
    const char* const player1Team;
    const char* const player1Strategy;
    const char* const player2Team;
    const char* const player2Strategy;
    const char* const pkmnDefs;
    const char* const moveDefs;
    const char* const typeDefs;
    const char* const itemDefs;
    const char* const args;
};

#endif // IMATCHDEFINITION_HPP
