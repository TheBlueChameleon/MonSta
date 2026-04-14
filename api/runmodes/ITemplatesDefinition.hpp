#ifndef ITEMPLATESDEFINITION_H
#define ITEMPLATESDEFINITION_H

struct ITemplatesDefinition
{
    const char* const engine;
    const char* const outputDirectory;
    const char* const player1Team;
    const char* const player1Strategy;
    const char* const player2Team;
    const char* const player2Strategy;
    const char* const pkmnDefs;
    const char* const moveDefs;
    const char* const typeDefs;
    const char* const itemDefs;
    const char* const args;

    const bool writeSchemas;
};

#endif // ITEMPLATESDEFINITION_H
