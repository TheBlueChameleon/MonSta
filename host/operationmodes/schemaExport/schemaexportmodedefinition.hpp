#ifndef SCHEMAEXPORTMODEDEFINITION_HPP
#define SCHEMAEXPORTMODEDEFINITION_HPP

#include "../../cli/cliinput.hpp"

#include <filesystem>

#include "../shared/basemodedefinition.hpp"

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
