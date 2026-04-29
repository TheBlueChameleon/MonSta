#ifndef PATHSDEFINITION_HPP
#define PATHSDEFINITION_HPP

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

#endif // PATHSDEFINITION_HPP
