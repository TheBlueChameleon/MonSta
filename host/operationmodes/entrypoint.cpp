#include <iostream>

#include "fileservice/fileservice.hpp"

#include "shared/basemodedefinition.hpp"
#include "shared/utils.hpp"

#include "operationmodes/help/entrypoint.hpp"
#include "operationmodes/remote/entrypoint.hpp"
#include "operationmodes/schemaExport/entrypoint.hpp"
#include "operationmodes/simulation/entrypoint.hpp"
#include "operationmodes/template/entrypoint.hpp"

#include "entrypoint.hpp"

namespace OperationModes
{
    void run(const std::shared_ptr<const BaseModeDefinition>& runDefinition)
    {
        switch (runDefinition->mode)
        {
            case OperationMode::SIMULATION:
                SimulationMode::run(
                    getAsSimulationModeDefinition(runDefinition)
                );
                break;
            case OperationMode::TEMPLATES:
                TemplateMode::run(
                    getAsTemplateModeDefinition(runDefinition)
                );
                break;
            case OperationMode::SCHEMAEXPORT:
                SchemaExportMode::run(
                    getAsSchemaExportModeDefinition(runDefinition)
                );
                break;
            case OperationMode::REMOTE:
                RemoteMode::run(
                    getAsRemoteModeDefinition(runDefinition)
                );
                break;
            case OperationMode::HELP:
                HelpMode::run(
                    getAsHelpModeDefinition(runDefinition)
                );
        }

        if (runDefinition->dryMode)
        {
            std::cout << "dry run summary:" << std::endl;
            for (const auto& info : FileService::getCreatedFileInfo())
            {
                std::cout << (info.overwritten ? "overwritten " : "new file    ") << "\t" << info.filename.c_str() << std::endl;
            }
            if (FileService::getCreatedFileInfo().empty())
            {
                std::cout << "-- none --" << std::endl;
            }
        }
    }
}
