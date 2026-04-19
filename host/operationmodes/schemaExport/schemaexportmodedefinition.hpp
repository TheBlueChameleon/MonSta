#ifndef SCHEMAEXPORTMODEDEFINITION_HPP
#define SCHEMAEXPORTMODEDEFINITION_HPP

#include <filesystem>

#include "cli/cliinput.hpp"

#include "operationmodes/shared/basemodedefinition.hpp"
#include "operationmodes/shared/defs/pathsdefinition.hpp"

namespace OperationModes
{
    struct SchemaExportModeDefinition : public BaseModeDefinition
    {
        SchemaExportModeDefinition(
            const CliInput& cli,
            const std::filesystem::path& outputDirectory
        ):
            BaseModeDefinition(cli, LoggingDefinition(), PathsDefinition()),
            outputDirectory(outputDirectory)
        {}

        std::filesystem::path outputDirectory;
    };
}

#endif // SCHEMAEXPORTMODEDEFINITION_HPP
