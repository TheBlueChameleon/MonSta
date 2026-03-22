#include <string>
using namespace std::string_literals;

#include "../../errors.hpp"

#include "safecast.hpp"

namespace RunDefinitionUtils
{
    template <typename T>
    const T getAsT(const std::shared_ptr<const BaseModeDefinition>& defs, const std::string& typeName)
    {
        const auto ptr = std::dynamic_pointer_cast<const T>(defs);
        if (ptr)
        {
            return *ptr;
        }
        else
        {
            throw IllegalStateException("Invalid cast: passed definition is not a "s + typeName);
        }
    }

    const HelpModeDefinition getAsHelpModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<HelpModeDefinition>(defs, "HelpModeDefinition");
    }

    const RemoteModeDefinition getAsRemoteModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<RemoteModeDefinition>(defs, "RemoteModeDefinition");
    }

    const SchemaExportModeDefinition getAsSchemaExportModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<SchemaExportModeDefinition>(defs, "SchemaExportModeDefinition");
    }

    const SimulationModeDefinition getAsSimulationModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<SimulationModeDefinition>(defs, "SimulationModeDefinition");
    }

    const TemplateModeDefinition getAsTemplateModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<TemplateModeDefinition>(defs, "TemplateModeDefinition");
    }
}
