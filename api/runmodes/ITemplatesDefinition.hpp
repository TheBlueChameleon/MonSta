#ifndef ITEMPLATESDEFINITION_HPP
#define ITEMPLATESDEFINITION_HPP

struct ITemplatesDefinition
{
    const bool writeSchemas;
    const bool writeAllowedValues;

    const char* const mechanicsDefinition;
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

#endif // ITEMPLATESDEFINITION_HPP
