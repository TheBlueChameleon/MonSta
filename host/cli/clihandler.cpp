#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
using namespace std::string_literals;

#include <argparse/argparse.hpp>
using ArgParser = argparse::ArgumentParser;

#include "../constants.hpp"
#include "../errors.hpp"

#include "clihandler.hpp"

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

CliInput::OperationMode modeFromString(const std::string& modeString)
{
    // *INDENT-OFF*
    if (modeString == CliInput::SIMULATION) return CliInput::OperationMode::SIMULATION;
    if (modeString == CliInput::TEMPLATE  ) return CliInput::OperationMode::TEMPLATE;
    if (modeString == CliInput::REMOTE    ) return CliInput::OperationMode::REMOTE;
    if (modeString == CliInput::HELP      ) return CliInput::OperationMode::HELP;
    // *INDENT-ON*

    return CliInput::OperationMode::INVALID;
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

void validateAsMode(const std::string& data)
{
    const auto mode = modeFromString(data);
    if (mode == CliInput::OperationMode::INVALID)
    {
        throw CriticalAbort("Invalid mode: "s + data);
    }
}

CliInput readAndValidateParser(const ArgParser& parser)
{
    const auto modeString = parser.get(CliInput::MODE);
    CliInput::OperationMode mode = modeFromString(modeString);

    const auto data = parser.get(CliInput::DATA);
    switch (mode)
    {
        case CliInput::OperationMode::SIMULATION:
        case CliInput::OperationMode::TEMPLATE:
            validateAsFile(data);
            break;
        case CliInput::OperationMode::REMOTE:
            validateAsRemote(data);
            break;
        case CliInput::OperationMode::HELP:
            validateAsMode(data);
            break;
        case CliInput::OperationMode::INVALID:
            {
                handleError("Illegal mode: '"s +  modeString + "'", parser);
            }
    }

    return CliInput(mode, data);
}

CliInput parseCliInput(const int argc, const char* const argv[])
{
    ArgParser parser(APP_NAME, APP_VERSION);
    configureParser(parser);
    runParser(parser, argc, argv);

    return readAndValidateParser(parser);
}

void showModeHelp(const std::string& data)
{
    const CliInput::OperationMode mode = modeFromString(data);
    std::cout << "Mode: '" << data << "'" << std::endl;
    switch (mode)
    {
        case CliInput::OperationMode::SIMULATION:
            std::cout << "Runs a sequence of match simulations and stores the results in a report file." << std::endl;
            std::cout << "'data' has to be the path to a run definition JSON file." << std::endl;
            std::cout << "Refer to the documentation for the structure of a run definition JSON file." << std::endl;
            break;
        case CliInput::OperationMode::TEMPLATE:
            std::cout << "Generates a template for a run definition JSON file and the files to be referenced therein." << std::endl;
            std::cout << "'data' has to be the path to a template definition JSON file." << std::endl;
            std::cout << "Refer to the documentation for the structure of a template definition JSON file." << std::endl;
            break;
        case CliInput::OperationMode::REMOTE:
            std::cout << "This mode has not yet been implemented" << std::endl;
            break;
        case CliInput::OperationMode::HELP:
            std::cout << "Shows help on the various run modes" << std::endl;
            break;
        case CliInput::OperationMode::INVALID:
            throw CriticalAbort("Invalid state: mode = "s + data);
    }

    std::exit(0);
}
