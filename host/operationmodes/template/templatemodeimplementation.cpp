#include <nlohmann/json.hpp>

#include <runmodes/ITemplatesDefinition.hpp>

#include "api/clientwrapper.hpp"

#include "fileservice/fileservice.hpp"
#include "jsonservice/jsonservice.hpp"
#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/schemavalidationconstants.hpp"
#include "operationmodes/shared/utils.hpp"

#include "templatemodedefinition.hpp"
#include "templatemodeimplementation.hpp"

namespace OperationModes
{
    static void writeSimulationDefinitionFile(
        const PathsDefinition& paths,
        const ITemplatesDefinition& clientDefinitions
    )
    {
        const auto UNDEFINED = "<to be defined>";

        using namespace nlohmann;
        ordered_json result = ordered_json::object();

        ordered_json& loggingDefinition = result[JKEY_LOGGING] = ordered_json::object();
        loggingDefinition[JKEY_LOGGING_LOGFILE] = UNDEFINED;
        loggingDefinition[JKEY_LOGGING_LOGLEVEL] = ILoggerService::LOGLEVELNAME_INFO;

        ordered_json& pathsDefinition = result[JKEY_PATHS] = ordered_json::object();
        pathsDefinition[JKEY_PATHS_INPUTDIRECTORY]  = paths.inputDirectory.c_str();
        pathsDefinition[JKEY_PATHS_OUTPUTDIRECTORY] = paths.outputDirectory.c_str();
        pathsDefinition[JKEY_PATHS_ENGINE]          = paths.engine.c_str();

        /*ordered_json& simulatorDefinition = */result[JKEY_SIMULATOR] = ordered_json::object();

        ordered_json& matchDefinition = result[JKEY_MATCHDEFINITION] = ordered_json::object();
        matchDefinition[JKEY_MATCHDEFINITION_MECHANICS]       = clientDefinitions.mechanicsDefinition;
        matchDefinition[JKEY_MATCHDEFINITION_PLAYER1TEAM]     = clientDefinitions.player1Team;
        matchDefinition[JKEY_MATCHDEFINITION_PLAYER1STRATETY] = clientDefinitions.player1Strategy;
        matchDefinition[JKEY_MATCHDEFINITION_PLAYER2TEAM]     = clientDefinitions.player2Team;
        matchDefinition[JKEY_MATCHDEFINITION_PLAYER2STRATETY] = clientDefinitions.player2Strategy;
        matchDefinition[JKEY_MATCHDEFINITION_PKMNDEFS]        = clientDefinitions.pkmnDefs;
        matchDefinition[JKEY_MATCHDEFINITION_MOVEDEFS]        = clientDefinitions.moveDefs;
        matchDefinition[JKEY_MATCHDEFINITION_TYPEDEFS]        = clientDefinitions.typeDefs;
        matchDefinition[JKEY_MATCHDEFINITION_ITEMDEFS]        = clientDefinitions.itemDefs;

        const auto& simSchema = JsonService::get(JTAG_SIMULATION);
        JsonService::validateAndPatch(result, simSchema, "<generated in TemplateMode>");

        FileService::write(filename_simulationDefinition, result.dump(2));
    }

    void runTemplateMode(const TemplateModeDefinition& defs)
    {
        setupLoggerService(defs.logging);
        setupFileService(defs);

        const auto enginePath = defs.paths.inputDirectory / defs.paths.engine;

        auto cw = ClientWrapper(enginePath);
        setupFileServiceOptions(cw, defs);

        auto clientDefinitions = cw.startTemplatesMode(
        {
            defs.templates.writeSchemas,
            defs.templates.writeAllowedValues,
            defs.templates.mechanicsDefinition.c_str(),
            defs.templates.player1Team.c_str(),
            defs.templates.player1Strategy.c_str(),
            defs.templates.player2Team.c_str(),
            defs.templates.player2Strategy.c_str(),
            defs.templates.pkmnDefs.c_str(),
            defs.templates.moveDefs.c_str(),
            defs.templates.typeDefs.c_str(),
            defs.templates.itemDefs.c_str(),
            defs.templates.args.data()
        });
        writeSimulationDefinitionFile(defs.paths, clientDefinitions);
    }
}
