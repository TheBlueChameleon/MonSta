#ifndef PATHSDEFINITION_H
#define PATHSDEFINITION_H

#include <filesystem>

namespace OperationModes
{
    struct PathsDefinition
    {
        const std::filesystem::path inputDirectory;
        const std::filesystem::path outputDirectory;
        const std::filesystem::path engine;
    };
}

#endif // PATHSDEFINITION_H
