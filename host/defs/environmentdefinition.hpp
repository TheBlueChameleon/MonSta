#ifndef ENVIRONMENTDEFINITION_H
#define ENVIRONMENTDEFINITION_H

#include <filesystem>

struct EnvironmentDefinition
{
    std::filesystem::path engine;
    std::filesystem::path inputDir;
    std::filesystem::path outputDir;

    int repetitions;
    int maxTurns;
    int threadCount;
};

#endif // ENVIRONMENTDEFINITION_H
