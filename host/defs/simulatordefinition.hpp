#ifndef SIMULATORDEFINITION_H
#define SIMULATORDEFINITION_H

#include <string>
#include <filesystem>

struct SimulatorDefinition
{
    const std::filesystem::path engine;
    const std::filesystem::path inputDir;
    const std::filesystem::path outputDir;

    const int repetitions;
    const int maxTurns;
    const int threadCount;

    const std::string args;
};

#endif // SIMULATORDEFINITION_H
