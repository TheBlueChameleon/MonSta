#ifndef SAFECAST_HPP
#define SAFECAST_HPP

#include <memory>

#include "helpmodedefinition.hpp"
#include "remoterundefinition.hpp"
#include "simulationmodedefinition.hpp"
#include "templatemodedefinition.hpp"

namespace RunDefinitionUtils
{
    const HelpModeDefinition       getAsHelpModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const RemoteModeDefinition     getAsRemoteModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const SimulationModeDefinition getAsSimulationModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
    const TemplateModeDefinition   getAsTemplateModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // SAFECAST_HPP
