#ifndef SIMULATORDEFINITION_H
#define SIMULATORDEFINITION_H

#include <string>
#include <filesystem>

struct SimulatorDefinition
{
    const std::filesystem::path engine;

    const int repetitions;
    const int maxTurns;
    const int threadCount;

    const std::string args;
};

#endif // SIMULATORDEFINITION_H
