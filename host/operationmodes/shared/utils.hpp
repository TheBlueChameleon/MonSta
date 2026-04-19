#ifndef UTILS_H
#define UTILS_H

#include <filesystem>
#include <memory>

class  ClientWrapper;

namespace OperationModes
{
    struct LoggingDefinition;
    struct BaseModeDefinition;
    struct HelpModeDefinition;
    struct RemoteModeDefinition;
    struct SchemaExportModeDefinition;
    struct SimulationModeDefinition;
    struct TemplateModeDefinition;

    const HelpModeDefinition&           getAsHelpModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const RemoteModeDefinition&         getAsRemoteModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const SchemaExportModeDefinition&   getAsSchemaExportModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const SimulationModeDefinition&     getAsSimulationModeDefinition(const std::shared_ptr<const BaseModeDefinition> defs);
    const TemplateModeDefinition&       getAsTemplateModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);

    void setupLoggerService(const LoggingDefinition& definition);
    void setupFileService(const BaseModeDefinition& definition);
    void setupClientWriteOptions(ClientWrapper& cw, const BaseModeDefinition& runDefinition);
}

#endif // UTILS_H
