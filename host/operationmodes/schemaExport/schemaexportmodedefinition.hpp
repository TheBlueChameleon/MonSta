#ifndef SCHEMAEXPORTMODEDEFINITION_HPP
#define SCHEMAEXPORTMODEDEFINITION_HPP

#include <filesystem>

#include "cli/cliinput.hpp"

#include "operationmodes/shared/basemodedefinition.hpp"

struct SchemaExportModeDefinition : public BaseModeDefinition
{
    SchemaExportModeDefinition(
        const CliInput& cli,
        const std::filesystem::path& outputDirectory
    ):
        BaseModeDefinition(cli, LoggingDefinition()),
        outputDirectory(outputDirectory)
    {}

    std::filesystem::path outputDirectory;
};

#endif // SCHEMAEXPORTMODEDEFINITION_HPP
