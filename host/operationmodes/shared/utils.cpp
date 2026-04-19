#include <string>

#include "errorservice/errors.hpp"

#include "fileservice/fileservice.hpp"

#include "api/clientwrapper.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/help/helpmodedefinition.hpp"
#include "operationmodes/remote/remoterundefinition.hpp"
#include "operationmodes/schemaExport/schemaexportmodedefinition.hpp"
#include "operationmodes/simulation/simulationmodedefinition.hpp"
#include "operationmodes/template/templatemodedefinition.hpp"

#include "utils.hpp"

using namespace std::string_literals;

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
            throw IllegalHostStateException("Invalid cast: passed definition is not a "s + typeName);
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

    void setupLoggerService(const LoggingDefinition& definition)
    {
        if (definition.logfile.has_value())
        {
            LoggerService::setLogFile(definition.logfile.value());
        }

        LoggerService::setLogLevel(definition.loglevel);
    }

    void setupFileService(const BaseModeDefinition& definition)
    {
        FileService::setOverwrite(definition.overwrite);
        FileService::setCreateDirectories(definition.createDirectories);
        FileService::setDryMode(definition.dryMode);

        try
        {
            FileService::setOutputBasePath(definition.paths.outputDirectory);

            if (!definition.paths.inputDirectory.empty())
            {
                FileService::setInputBasePath(definition.paths.inputDirectory);
            }
        }
        catch (const IOError& e)
        {
            throw InvalidUserInput(
                "Error while processing run configuration:\n"s +
                e.what()
            );
        }
    }

    void setupFileServiceOptions(ClientWrapper& cw, const BaseModeDefinition& runDefinition)
    {
        cw.setFileServiceDefinition(IFileServiceDefinition
        {
            runDefinition.overwrite,
            runDefinition.createDirectories,
            runDefinition.dryMode,

            runDefinition.paths.inputDirectory.c_str(),
            runDefinition.paths.outputDirectory.c_str(),
            runDefinition.paths.engine.c_str()
        });

    }

}
