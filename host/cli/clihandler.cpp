#include <filesystem>
#include <iostream>
#include <stdexcept>
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

    throw std::invalid_argument("Invalid mode identifier: '"s + modeString + "'");
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
    throw CriticalAbort("Operation mode '"s + CliInput::REMOTE + "' not implemented yet");
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

LoggingDefinition unpackLoggingDefinition(const Json& data)
{
    std::optional<std::filesystem::path> logfile;
    ILoggerService::LogLevel             loglevel;

    if (data.is_structured())       // eqv. to is not null
    {
        if (data.contains(JKEY_LOGGING_LOGLEVEL))
        {
            loglevel = data[JKEY_LOGGING_LOGLEVEL];
        }

        if (data.contains(JKEY_LOGGING_LOGFILE))
        {
            logfile = data[JKEY_LOGGING_LOGFILE];
        }
    }

    return LoggingDefinition(logfile, loglevel);
}

// .......................................................................... //
// simulation

SimulatorDefinition unpackSimulatorDefinition(const Json& data)
{
    std::filesystem::path engine;
    std::filesystem::path inputDir;
    std::filesystem::path outputDir;
    int repetitions;
    int maxTurns;
    int threadCount;
    std::string args;

    // TODO!

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
    std::filesystem::path player1Team;
    std::filesystem::path player1Strategy;
    std::filesystem::path player2Team;
    std::filesystem::path player2Strategy;
    std::filesystem::path pkmnDefs;
    std::filesystem::path moveDefs;
    std::filesystem::path typeDefs;

    // TODO!

    return MatchDefinition(
               player1Team,
               player1Strategy,
               player2Team,
               player2Strategy,
               pkmnDefs,
               moveDefs,
               typeDefs
           );
}

std::shared_ptr<const BaseModeDefinition> unpackSimulationInput(const char* const source)
{
    Json data = JsonService::readJsonFile(source);
    JsonService::validateJsonAgainstJson(data, SCHEMA_SIMULATION, source);
    const auto logging   = unpackLoggingDefinition(data[JKEY_LOGGING]);
    const auto simulator = unpackSimulatorDefinition(data[JKEY_SIMULATOR]);

    // TODO! MatchDefinition

    return std::make_shared<SimulationModeDefinition>(logging, simulator, MatchDefinition());
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
    catch (const std::invalid_argument& err)
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

    throw std::invalid_argument(
        "Unrecognized mode id "s + std::to_string(static_cast<int>(cliInput.mode))
    );
}

// ========================================================================== //
// showModeHelp

void showModeHelp(const OperationMode mode)
{
    switch (mode)
    {
        case OperationMode::SIMULATION:
            std::cout << "Runs a sequence of match simulations and stores the results in a report file." << std::endl;
            std::cout << "'data' has to be the path to a run definition JSON file." << std::endl;
            std::cout << "Refer to the documentation for the structure of a run definition JSON file." << std::endl;
            break;
        case OperationMode::TEMPLATE:
            std::cout << "Generates a template for a run definition JSON file and the files to be referenced therein." << std::endl;
            std::cout << "'data' has to be the path to a template definition JSON file." << std::endl;
            std::cout << "Refer to the documentation for the structure of a template definition JSON file." << std::endl;
            break;
        case OperationMode::REMOTE:
            std::cout << "This mode has not yet been implemented" << std::endl;
            break;
        case OperationMode::HELP:
            std::cout << "Shows help on the various run modes" << std::endl;
            break;
    }

    std::exit(0);
}
