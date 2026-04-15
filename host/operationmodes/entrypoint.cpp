#include <iostream>

#include "fileservice/fileservice.hpp"
#include "loggerservice/loggerservice.hpp"

#include "shared/basemodedefinition.hpp"
#include "shared/utils.hpp"

#include "operationmodes/help/helpmodeimplementation.hpp"
#include "operationmodes/help/helpmodedefinition.hpp"

#include "operationmodes/remote/remotemodeimplemetnation.hpp"

#include "operationmodes/schemaExport/schemaexportmodeimplementation.hpp"
#include "operationmodes/schemaExport/schemaexportmodedefinition.hpp"

#include "operationmodes/simulation/simulationmodeimplementation.hpp"
#include "operationmodes/simulation/simulationmodedefinition.hpp"

#include "operationmodes/template/templatemodeimplementation.hpp"
#include "operationmodes/template/templatemodedefinition.hpp"

#include "entrypoint.hpp"

namespace OperationModes
{
    void run(const std::shared_ptr<const BaseModeDefinition>& runDefinition)
    {
        switch (runDefinition->mode)
        {
            case OperationMode::SIMULATION:
                runSimulationMode(
                    getAsSimulationModeDefinition(runDefinition)
                );
                break;
            case OperationMode::TEMPLATES:
                runTemplateMode(
                    getAsTemplateModeDefinition(runDefinition)
                );
                break;
            case OperationMode::SCHEMAEXPORT:
                runSchemaExportMode(
                    getAsSchemaExportModeDefinition(runDefinition)
                );
                break;
            case OperationMode::REMOTE:
                runRemoteMode(
                    getAsRemoteModeDefinition(runDefinition)
                );
                break;
            case OperationMode::HELP:
                runHelpMode(
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
