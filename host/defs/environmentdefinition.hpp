#ifndef ENVIRONMENTDEFINITION_H
#define ENVIRONMENTDEFINITION_H

#include <filesystem>

#include <ILogger.hpp>

struct EnvironmentDefinition
{
    std::filesystem::path engine;
    std::filesystem::path logfile;
    std::filesystem::path output;

    ILogger::LogLevel loglevel;
    int repetitions;
    int maxTurns;
    int threadCount;
};

#endif // ENVIRONMENTDEFINITION_H
