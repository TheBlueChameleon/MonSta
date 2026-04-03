#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include <string_view>
using namespace std::string_literals;

#include <argparse/argparse.hpp>
using ArgParser = argparse::ArgumentParser;

#include <nlohmann/json.hpp>
using namespace nlohmann;
#include <nlohmann/json-schema.hpp>
using namespace nlohmann::json_schema;

#include "constants.hpp"
#include "errors.hpp"

#include "fileservice/fileservice.hpp"

#include "jsonservice/jsonservice.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/help/helpmodedefinition.hpp"
#include "operationmodes/remote/remoterundefinition.hpp"
#include "operationmodes/schemaExport/schemaexportmodedefinition.hpp"
#include "operationmodes/simulation/simulationmodedefinition.hpp"
#include "operationmodes/template/templatemodedefinition.hpp"
#include "operationmodes/shared/schemavalidationconstants.hpp"

#include "clihandler.hpp"

// ========================================================================== //
// readCliInput

static void configureParser(ArgParser& parser)
{
    parser.add_argument(CliInput::MODE)
    .nargs(1)
    .help("Sets the operation mode.\n"
          "One of "s +
          CliInput::SIMULATION + ", " +
          CliInput::TEMPLATES + ", " +
          CliInput::SCHEMAEXPORT + ", " +
          CliInput::REMOTE + ", " +
          CliInput::HELP + "."
         );

    parser.add_argument(CliInput::DATA)
    .help("The data to be processed.\n"
          "Use "s + CliInput::HELP + " <mode> for details."
         );

#define makeFlag(str) "-"s + str[0], "--"s + str
    parser.add_argument(makeFlag(CliInput::OVERWRITE))
    .help("overwrite files if already existing")
    .flag();

    parser.add_argument(makeFlag(CliInput::CREATE_DIRECTORIES))
    .help("creates output directories if not yet existing")
    .flag();

    parser.add_argument(makeFlag(CliInput::DRY_MODE))
    .help("only lists which files would be (over)written")
    .flag();
#undef makeFlag
}

static void handleError(const std::string_view errorMessage, const ArgParser& parser)
{
    std::stringstream ss;
    ss << errorMessage << std::endl;
    ss << std::endl;
    ss << parser << std::endl;

    throw CriticalAbort(ss.str());
}

static void runParser(ArgParser& parser, const int argc, const char* const argv[])
{
    if (argc == 1)
    {
        std::cout << parser << std::endl;
        std::exit(1);
    }

    try
    {
        parser.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        handleError(err.what(), parser);
    }
}

static OperationMode modeFromString(const std::string_view modeString)
{
    // *INDENT-OFF*
    if (modeString == CliInput::SIMULATION  ) return OperationMode::SIMULATION;
    if (modeString == CliInput::TEMPLATES    ) return OperationMode::TEMPLATES;
    if (modeString == CliInput::SCHEMAEXPORT) return OperationMode::SCHEMAEXPORT;
    if (modeString == CliInput::REMOTE      ) return OperationMode::REMOTE;
    if (modeString == CliInput::HELP        ) return OperationMode::HELP;
    // *INDENT-ON*

    throw IllegalStateException("Invalid mode identifier: '"s + modeString.data() + "'");
}

static void validateAsInputFile(const std::string_view data)
{
    const auto path = std::filesystem::path(data);

    if (!std::filesystem::exists(path))
    {
        throw CriticalAbort("'"s + data.data() + "' does not exist.");
    }

    // TODO: check if this also works with symlinks
    if (!std::filesystem::is_regular_file(path))
    {
        throw CriticalAbort("'"s + data.data() + "' is not a file.");
    }
}

static void validateAsOutputDirectory(const std::string_view data)
{
    const auto path = std::filesystem::path(data);

    if (FileService::isSpecialPath(path))
    {
        return;
    }

    if (std::filesystem::exists(path))
    {
        if (!std::filesystem::is_directory(path))
        {
            throw CriticalAbort("'"s + data.data() + "' is not a directory.");
        }
    }
}

static void validateAsRemote(const std::string_view data)
{
    // TODO
}

static CliInput readAndValidateParser(const ArgParser& parser)
{
    const auto modeString = parser.get(CliInput::MODE);
    OperationMode mode = modeFromString(modeString);

    const auto data = parser.get(CliInput::DATA);
#define getFlag(flagName) parser.get<bool>(flagName)
    const auto overwrite  = getFlag(CliInput::OVERWRITE);
    const auto createDirs = getFlag(CliInput::CREATE_DIRECTORIES);
    const auto dryMode    = getFlag(CliInput::DRY_MODE);
#undef getFlag

    switch (mode)
    {
        case OperationMode::SIMULATION:
        case OperationMode::TEMPLATES:
            validateAsInputFile(data);
            break;
        case OperationMode::SCHEMAEXPORT:
            validateAsOutputDirectory(data);
            break;
        case OperationMode::REMOTE:
            validateAsRemote(data);
            break;
        case OperationMode::HELP:
            break;
    }

    return CliInput(mode, data, overwrite, createDirs, dryMode);
}

CliInput readCliInput(const int argc, const char* const argv[])
{
    ArgParser parser(APP_NAME, APP_VERSION);
    configureParser(parser);
    runParser(parser, argc, argv);

    return readAndValidateParser(parser);
}

// ========================================================================== //
// handleCliInput

// .......................................................................... //
// shared

template<typename T>
static void fetchIfInJson(const char* const jsonKey, const ordered_json& data, T& target)
{
    if (data.contains(jsonKey))
    {
        target = data[jsonKey];
    }
}

static LoggingDefinition unpackLoggingDefinition(const ordered_json& data)
{
    ILoggerService::LogLevel             loglevel;
    std::optional<std::filesystem::path> logfile;

    // JKEY_LOGGING exists due to having a default
    fetchIfInJson(JKEY_LOGGING_LOGLEVEL, data, loglevel);
    fetchIfInJson(JKEY_LOGGING_LOGFILE, data, logfile);

    return LoggingDefinition(logfile, loglevel);
}

// .......................................................................... //
// simulation

static SimulatorDefinition unpackSimulatorDefinition(const ordered_json& data)
{
    std::string engine = data[JKEY_SIMULATOR_ENGINE];   // required to exist.
    std::string inputDir;
    std::string outputDir;
    int repetitions;
    int maxTurns;
    int threadCount;
    std::string args;

    fetchIfInJson(JKEY_SIMULATOR_INPUTDIRECTORY,  data, inputDir);
    fetchIfInJson(JKEY_SIMULATOR_OUTPUTDIRECTORY, data, outputDir);
    fetchIfInJson(JKEY_SIMULATOR_REPETITIONS,     data, repetitions);
    fetchIfInJson(JKEY_SIMULATOR_MAXTURNS,        data, maxTurns);
    fetchIfInJson(JKEY_SIMULATOR_THREADCOUNT,     data, threadCount);
    fetchIfInJson(JKEY_SIMULATOR_ARGS,            data, args);

    return SimulatorDefinition
    {
        engine,
        inputDir,
        outputDir,
        repetitions,
        maxTurns,
        threadCount,
        args
    };
}

static MatchDefinition unpackMatchDefinition(const ordered_json& data)
{
    // all entries required
    return MatchDefinition(
               data[JKEY_MATCHDEFINITION_PLAYER1TEAM],
               data[JKEY_MATCHDEFINITION_PLAYER1STRATETY],
               data[JKEY_MATCHDEFINITION_PLAYER2TEAM],
               data[JKEY_MATCHDEFINITION_PLAYER2STRATETY],
               data[JKEY_MATCHDEFINITION_PKMNDEFS],
               data[JKEY_MATCHDEFINITION_MOVEDEFS],
               data[JKEY_MATCHDEFINITION_TYPEDEFS],
               data[JKEY_MATCHDEFINITION_ITEMDEFS]
           );
}

static std::shared_ptr<const BaseModeDefinition> unpackSimulationInput(const CliInput& cliInput)
{
    const std::string_view source = cliInput.data;
    auto data = JsonService::readValidateByTagPatchAndAdd(
                    std::string(JTAG_BASE) + source.data(),
                    source,
                    JTAG_SIMULATION
                );

    return std::make_shared<SimulationModeDefinition>(
               cliInput,
               unpackLoggingDefinition(data[JKEY_LOGGING]),
               unpackSimulatorDefinition(data[JKEY_SIMULATOR]),
               unpackMatchDefinition(data[JKEY_MATCHDEFINITION])
           );
}

// .......................................................................... //
// template

static TemplatesDefinition unpackTemplatesDefinition(const ordered_json& data)
{
    std::string engine          = data[JKEY_TEMPLATES_ENGINE];                  // required to exist.
    std::string outputDirectory = data[JKEY_TEMPLATES_OUTPUTDIRECTORY];         // required to exist.
    std::string player1Team;
    std::string player1Strategy;
    std::string player2Team;
    std::string player2Strategy;
    std::string pkmnDefs;
    std::string moveDefs;
    std::string typeDefs;
    std::string itemDefs;
    bool writeSchemas = data[JKEY_TEMPLATES_WRITESCHEMAS];                      // exists by default
    std::string args;

    fetchIfInJson(JKEY_TEMPLATES_PLAYER1TEAM,       data, player1Team);
    fetchIfInJson(JKEY_TEMPLATES_PLAYER1STRATEGY,   data, player1Strategy);
    fetchIfInJson(JKEY_TEMPLATES_PLAYER2TEAM,       data, player2Team);
    fetchIfInJson(JKEY_TEMPLATES_PLAYER2STRATEGY,   data, player2Strategy);
    fetchIfInJson(JKEY_TEMPLATES_PKMNDEFS,          data, pkmnDefs);
    fetchIfInJson(JKEY_TEMPLATES_MOVEDEFS,          data, moveDefs);
    fetchIfInJson(JKEY_TEMPLATES_TYPEDEFS,          data, typeDefs);
    fetchIfInJson(JKEY_TEMPLATES_ITEMDEFS,          data, itemDefs);
    fetchIfInJson(JKEY_TEMPLATES_ARGS,              data, args);

    return TemplatesDefinition
    {
        engine,
        outputDirectory,
        player1Team,
        player1Strategy,
        player2Team,
        player2Strategy,
        pkmnDefs,
        moveDefs,
        typeDefs,
        itemDefs,
        writeSchemas,
        args
    };
}

static std::shared_ptr<const BaseModeDefinition> unpackTemplateInput(const CliInput& cliInput)
{
    const std::string_view source = cliInput.data;
    auto data = JsonService::readValidateByTagPatchAndAdd(
                    std::string(JTAG_BASE) + source.data(),
                    source,
                    JTAG_TEMPLATES
                );

    return std::make_shared<TemplateModeDefinition>(
               cliInput,
               unpackLoggingDefinition(data[JKEY_LOGGING]),
               unpackTemplatesDefinition(data[JKEY_TEMPLATES])
           );
}

// .......................................................................... //
// schema export

static std::shared_ptr<const BaseModeDefinition> unpackSchemaExportInput(const CliInput& cliInput)
{
    const std::string_view outputDirectory = cliInput.data;
    return std::make_shared<SchemaExportModeDefinition>(cliInput, outputDirectory);
}

// .......................................................................... //
// remote

static std::shared_ptr<const BaseModeDefinition> unpackRemoteInput(const CliInput& cliInput)
{
    const std::string_view socket = cliInput.data;

    //TODO

    return std::make_shared<RemoteModeDefinition>(cliInput);
}

// .......................................................................... //
// help

static std::shared_ptr<const BaseModeDefinition> unpackHelpInput(const CliInput& cliInput)
{
    const std::string_view target = cliInput.data;
    try
    {
        const auto mode = modeFromString(target);
        return std::make_shared<HelpModeDefinition>(cliInput, mode);
    }
    catch (const IllegalStateException& err)
    {
        throw CriticalAbort("No help available for unknown mode '"s + target.data() + "'");
    }
}

// .......................................................................... //
// base

std::shared_ptr<const BaseModeDefinition> unpackCliInput(const CliInput& cliInput)
{
    switch (cliInput.mode)
    {
        case OperationMode::SIMULATION:
            return unpackSimulationInput(cliInput);
        case OperationMode::TEMPLATES:
            return unpackTemplateInput(cliInput);
        case OperationMode::SCHEMAEXPORT:
            return unpackSchemaExportInput(cliInput);
        case OperationMode::REMOTE:
            return unpackRemoteInput(cliInput);
        case OperationMode::HELP:
            return unpackHelpInput(cliInput);
    }

    throw IllegalStateException(
        "Unrecognized mode id "s + std::to_string(static_cast<int>(cliInput.mode))
    );
}
