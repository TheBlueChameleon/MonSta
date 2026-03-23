#ifndef SAFECAST_HPP
#define SAFECAST_HPP

#include <memory>

struct BaseModeDefinition;
struct HelpModeDefinition;
struct RemoteModeDefinition;
struct SchemaExportModeDefinition;
struct SimulationModeDefinition;
struct TemplateModeDefinition;

namespace RunDefinitionUtils
{
    const HelpModeDefinition         getAsHelpModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const RemoteModeDefinition       getAsRemoteModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const SchemaExportModeDefinition getAsSchemaExportModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const SimulationModeDefinition   getAsSimulationModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const TemplateModeDefinition     getAsTemplateModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // SAFECAST_HPP
