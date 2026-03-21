#ifndef SIMULATORDEFINITION_H
#define SIMULATORDEFINITION_H

#include <filesystem>

struct SimulatorDefinition
{
    const std::filesystem::path engine;
    const std::filesystem::path inputDir;
    const std::filesystem::path outputDir;

    const int repetitions;
    const int maxTurns;
    const int threadCount;
};

#endif // SIMULATORDEFINITION_H
