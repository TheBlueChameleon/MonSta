#include <string>
using namespace std::string_literals;

#include "errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/help/helpmodedefinition.hpp"
#include "operationmodes/remote/remoterundefinition.hpp"
#include "operationmodes/schemaExport/schemaexportmodedefinition.hpp"
#include "operationmodes/simulation/simulationmodedefinition.hpp"
#include "operationmodes/template/templatemodedefinition.hpp"

#include "utils.hpp"

namespace OperationModes
{
    template <typename T>
    const T& getAsT(const std::shared_ptr<const BaseModeDefinition>& defs, const std::string& typeName)
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

    const HelpModeDefinition& getAsHelpModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<HelpModeDefinition>(defs, "HelpModeDefinition");
    }

    const RemoteModeDefinition& getAsRemoteModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<RemoteModeDefinition>(defs, "RemoteModeDefinition");
    }

    const SchemaExportModeDefinition& getAsSchemaExportModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<SchemaExportModeDefinition>(defs, "SchemaExportModeDefinition");
    }

    const SimulationModeDefinition& getAsSimulationModeDefinition(const std::shared_ptr<const BaseModeDefinition> defs)
    {
        return getAsT<SimulationModeDefinition>(defs, "SimulationModeDefinition");
    }

    const TemplateModeDefinition& getAsTemplateModeDefinition(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        return getAsT<TemplateModeDefinition>(defs, "TemplateModeDefinition");
    }

    void setupLogger(const LoggingDefinition& def)
    {
        if (def.logfile.has_value())
        {
            LoggerService::setLogFile(def.logfile.value());
        }

        LoggerService::setLogLevel(def.loglevel);
    }
}
