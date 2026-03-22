#ifndef SCHEMAEXPORTMODEDEFINITION_HPP
#define SCHEMAEXPORTMODEDEFINITION_HPP

#include <filesystem>

#include "basemodedefinition.hpp"

struct SchemaExportModeDefinition : public BaseModeDefinition
{
    SchemaExportModeDefinition(const std::filesystem::path& outputDirectory):
        BaseModeDefinition(OperationMode::SCHEMAEXPORT, LoggingDefinition()),
        outputDirectory(outputDirectory)
    {}

    std::filesystem::path outputDirectory;
};

#endif // SCHEMAEXPORTMODEDEFINITION_HPP
