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

#include "errorservice/errors.hpp"

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

using namespace OperationModes;

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

    throw InvalidUserInput(ss.str());
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

    throw IllegalHostStateException("Invalid mode identifier: '"s + modeString.data() + "'");
}

static void validateAsInputFile(const std::string_view data)
{
    const auto path = std::filesystem::path(data);

    if (!std::filesystem::exists(path))
    {
        throw InvalidUserInput("'"s + data.data() + "' does not exist.");
    }

    // TODO: check if this also works with symlinks
    if (!std::filesystem::is_regular_file(path))
    {
        throw InvalidUserInput("'"s + data.data() + "' is not a file.");
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
            throw InvalidUserInput("'"s + data.data() + "' is not a directory.");
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
static const T fetchIfInJson(const ordered_json& data, const char* const jsonKey, const T& defaultValue)
{
    if (data.contains(jsonKey))
    {
        return data[jsonKey];
    }
    else
    {
        return defaultValue;
    }
}

static LoggingDefinition unpackLoggingDefinition(const ordered_json& data)
{
    // JKEY_LOGGING exists due to having a default
    return LoggingDefinition(
               fetchIfInJson(data, JKEY_LOGGING_LOGFILE, std::filesystem::path{}),
               LoggerService::getLogLevelFromName(
                   fetchIfInJson(data, JKEY_LOGGING_LOGLEVEL, std::string(ILoggerService::LOGLEVELNAME_OFF))
               )
           );
}

// .......................................................................... //
// simulation

static SimulatorDefinition unpackSimulatorDefinition(const ordered_json& data)
{
    return SimulatorDefinition
    {
        data               [JKEY_SIMULATOR_ENGINE],
        fetchIfInJson(data, JKEY_SIMULATOR_INPUTDIRECTORY,  std::filesystem::path {}),
        fetchIfInJson(data, JKEY_SIMULATOR_OUTPUTDIRECTORY, std::filesystem::path {}),
        data               [JKEY_SIMULATOR_REPETITIONS],
        data               [JKEY_SIMULATOR_MAXTURNS],
        data               [JKEY_SIMULATOR_THREADCOUNT],
        fetchIfInJson(data, JKEY_SIMULATOR_OUTPUTDIRECTORY, std::string {}),
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
    const std::string tag = std::string(JTAG_BASE.name) + source.data();
    auto data = JsonService::readValidateByTagPatchAndAdd(
                    tag.data(),
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
    return TemplatesDefinition
    {
        data               [JKEY_TEMPLATES_ENGINE],
        data               [JKEY_TEMPLATES_OUTPUTDIRECTORY],
        fetchIfInJson(data, JKEY_TEMPLATES_PLAYER1TEAM, std::filesystem::path {}),
        fetchIfInJson(data, JKEY_TEMPLATES_PLAYER1STRATEGY, std::filesystem::path {}),
        fetchIfInJson(data, JKEY_TEMPLATES_PLAYER2TEAM, std::filesystem::path {}),
        fetchIfInJson(data, JKEY_TEMPLATES_PLAYER2STRATEGY, std::filesystem::path {}),
        fetchIfInJson(data, JKEY_TEMPLATES_PKMNDEFS, std::filesystem::path {}),
        fetchIfInJson(data, JKEY_TEMPLATES_MOVEDEFS, std::filesystem::path {}),
        fetchIfInJson(data, JKEY_TEMPLATES_TYPEDEFS, std::filesystem::path {}),
        fetchIfInJson(data, JKEY_TEMPLATES_ITEMDEFS, std::filesystem::path {}),
        data               [JKEY_TEMPLATES_WRITESCHEMAS],
        fetchIfInJson(data, JKEY_TEMPLATES_ARGS, std::filesystem::path {}),
    };
}

static std::shared_ptr<const BaseModeDefinition> unpackTemplateInput(const CliInput& cliInput)
{
    const std::string_view source = cliInput.data;
    const std::string tag = std::string(JTAG_BASE.name) + source.data();
    auto data = JsonService::readValidateByTagPatchAndAdd(
                    tag.data(),
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
    catch (const IllegalHostStateException& err)
    {
        throw InvalidUserInput("No help available for unknown mode '"s + target.data() + "'");
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

    throw IllegalHostStateException(
        "Unrecognized mode id "s + std::to_string(static_cast<int>(cliInput.mode))
    );
}
