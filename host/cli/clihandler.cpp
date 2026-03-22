#include <filesystem>
#include <sstream>
#include <string>
using namespace std::string_literals;

#include <argparse/argparse.hpp>
using ArgParser = argparse::ArgumentParser;

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>
using Json = nlohmann::json;
using JsonValidator = nlohmann::json_schema::json_validator;

#include "../api/loggerservice.hpp"

#include "../defs/helpmodedefinition.hpp"
#include "../defs/loggingdefinition.hpp"
#include "../defs/remoterundefinition.hpp"
#include "../defs/simulationmodedefinition.hpp"
#include "../defs/templatemodedefinition.hpp"

#include "../json/jsonservice.hpp"

#include "../constants.hpp"
#include "../errors.hpp"

#include "clihandler.hpp"

// ========================================================================== //
// readCliInput

void configureParser(ArgParser& parser)
{
    parser.add_argument(CliInput::MODE)
    .nargs(1)
    .help("Sets the processing mode.\n"
          "One of "s +
          CliInput::SIMULATION + ", " +
          CliInput::TEMPLATE + ", " +
          CliInput::REMOTE + ", " +
          CliInput::HELP + "."
         );

    parser.add_argument(CliInput::DATA)
    .help("The data to be processed.\n"
          "Use "s + CliInput::HELP + " <mode> for details."
         );
}

void handleError(const std::string& errorMessage, const ArgParser& parser)
{
    std::stringstream ss;
    ss << errorMessage << std::endl;
    ss << std::endl;
    ss << parser << std::endl;

    throw CriticalAbort(ss.str());
}

void runParser(ArgParser& parser, const int argc, const char* const argv[])
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

OperationMode modeFromString(const std::string& modeString)
{
    // *INDENT-OFF*
    if (modeString == CliInput::SIMULATION) return OperationMode::SIMULATION;
    if (modeString == CliInput::TEMPLATE  ) return OperationMode::TEMPLATE;
    if (modeString == CliInput::REMOTE    ) return OperationMode::REMOTE;
    if (modeString == CliInput::HELP      ) return OperationMode::HELP;
    // *INDENT-ON*

    throw IllegalStateException("Invalid mode identifier: '"s + modeString + "'");
}

void validateAsFile(const std::string& data)
{
    const auto path = std::filesystem::path(data);

    if (!std::filesystem::exists(path))
    {
        throw CriticalAbort("'"s + data + "' does not exist.");
    }
}

void validateAsRemote(const std::string& data)
{
    // TODO
}

CliInput readAndValidateParser(const ArgParser& parser)
{
    const auto modeString = parser.get(CliInput::MODE);
    OperationMode mode = modeFromString(modeString);

    const auto data = parser.get(CliInput::DATA);
    switch (mode)
    {
        case OperationMode::SIMULATION:
        case OperationMode::TEMPLATE:
            validateAsFile(data);
            break;
        case OperationMode::REMOTE:
            validateAsRemote(data);
            break;
        case OperationMode::HELP:
            break;
    }

    return CliInput(mode, data);
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
void fetchIfInJson(const char* const jsonKey, const Json& data, T& target)
{
    if (data.contains(jsonKey))
    {
        target = data[jsonKey];
    }
}

LoggingDefinition unpackLoggingDefinition(const Json& data)
{
    std::optional<std::filesystem::path> logfile;
    ILoggerService::LogLevel             loglevel;

    if (data.is_structured())       // eqv. to is not null
    {
        fetchIfInJson(JKEY_LOGGING_LOGLEVEL, data, loglevel);
        fetchIfInJson(JKEY_LOGGING_LOGFILE, data, logfile);
    }

    return LoggingDefinition(logfile, loglevel);
}

// .......................................................................... //
// simulation

SimulatorDefinition unpackSimulatorDefinition(const Json& data)
{
    std::string engine = data[JKEY_SIMULATOR_ENGINE];   // required to exist.
    std::string inputDir;
    std::string outputDir;
    int repetitions;
    int maxTurns;
    int threadCount;
    std::string args;

    fetchIfInJson(JKEY_SIMULATOR_INPUTDIRECTORY, data, inputDir);
    fetchIfInJson(JKEY_SIMULATOR_OUTPUTDIRECTORY, data, outputDir);
    fetchIfInJson(JKEY_SIMULATOR_REPETITIONS, data, repetitions);
    fetchIfInJson(JKEY_SIMULATOR_MAXTURNS, data, maxTurns);
    fetchIfInJson(JKEY_SIMULATOR_THREADCOUNT, data, threadCount);
    fetchIfInJson(JKEY_SIMULATOR_ARGS, data, args);

    return SimulatorDefinition(
               engine,
               inputDir,
               outputDir,
               repetitions,
               maxTurns,
               threadCount,
               args
           );
}

MatchDefinition unpackMatchDefinition(const Json& data)
{
    // all entries required
    return MatchDefinition(
               data[JKEY_MATCHDEFINITION_PLAYER1TEAM],
               data[JKEY_MATCHDEFINITION_PLAYER1STRATETY],
               data[JKEY_MATCHDEFINITION_PLAYER2TEAM],
               data[JKEY_MATCHDEFINITION_PLAYER2STRATETY],
               data[JKEY_MATCHDEFINITION_PKMNDEFS],
               data[JKEY_MATCHDEFINITION_MOVEDEFS],
               data[JKEY_MATCHDEFINITION_TYPEDEFS]
           );
}

std::shared_ptr<const BaseModeDefinition> unpackSimulationInput(const char* const source)
{
    Json data = JsonService::readJsonFile(source);
    JsonService::validateJsonAgainstJson(data, SCHEMA_SIMULATION, source);

    return std::make_shared<SimulationModeDefinition>(
               unpackLoggingDefinition(data[JKEY_LOGGING]),
               unpackSimulatorDefinition(data[JKEY_SIMULATOR]),
               unpackMatchDefinition(data[JKEY_MATCHDEFINITION])
           );
}

// .......................................................................... //
// template

std::shared_ptr<const BaseModeDefinition> unpackTemplateInput(const char* const source)
{
    //TODO

    return std::make_shared<TemplateModeDefinition>();
}

// .......................................................................... //
// remote

std::shared_ptr<const BaseModeDefinition> unpackRemoteInput(const std::string& socket)
{
    //TODO

    return std::make_shared<RemoteModeDefinition>();
}

// .......................................................................... //
// help

std::shared_ptr<const BaseModeDefinition> unpackHelpInput(const std::string& target)
{
    try
    {
        const auto mode = modeFromString(target);
        return std::make_shared<HelpModeDefinition>(mode);
    }
    catch (const IllegalStateException& err)
    {
        throw CriticalAbort("No help available for unknown mode '"s + target + "'");
    }
}

// .......................................................................... //
// base

std::shared_ptr<const BaseModeDefinition> unpackCliInput(const CliInput& cliInput)
{
    switch (cliInput.mode)
    {
        case OperationMode::SIMULATION:
            return unpackSimulationInput(cliInput.data.c_str());
        case OperationMode::TEMPLATE:
            return unpackTemplateInput(cliInput.data.c_str());
        case OperationMode::REMOTE:
            return unpackRemoteInput(cliInput.data);
        case OperationMode::HELP:
            return unpackHelpInput(cliInput.data);
    }

    throw IllegalStateException(
        "Unrecognized mode id "s + std::to_string(static_cast<int>(cliInput.mode))
    );
}


