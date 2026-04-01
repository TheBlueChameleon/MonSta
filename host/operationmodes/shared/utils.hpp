#ifndef UTILS_H
#define UTILS_H

#include <filesystem>
#include <memory>

struct BaseModeDefinition;
struct HelpModeDefinition;
struct RemoteModeDefinition;
struct SchemaExportModeDefinition;
struct SimulationModeDefinition;
struct TemplateModeDefinition;

struct LoggingDefinition;

namespace OperationModes
{
    const HelpModeDefinition&           getAsHelpModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const RemoteModeDefinition&         getAsRemoteModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const SchemaExportModeDefinition&   getAsSchemaExportModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const SimulationModeDefinition&     getAsSimulationModeDefinition(const std::shared_ptr<const BaseModeDefinition> defs);
    const TemplateModeDefinition&       getAsTemplateModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);

    void setupLoggerService(const LoggingDefinition& definition);
    void setupFileService(const BaseModeDefinition& definition, const std::filesystem::path& outputDirectory);
}

#endif // UTILS_H
