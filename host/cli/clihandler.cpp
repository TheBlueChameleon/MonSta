#include <filesystem>
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
    .choices(CliInput::SIMULATION, CliInput::TEMPLATE, CliInput::REMOTE, CliInput::HELP)
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

void handleErr(const std::exception& err, const ArgParser& parser)
{
    std::stringstream ss;
    ss << err.what() << std::endl;
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
        handleErr(err, parser);
    }
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
    // *INDENT-OFF*
    if (data == CliInput::SIMULATION) return;
    if (data == CliInput::TEMPLATE  ) return;
    if (data == CliInput::REMOTE    ) return;
    if (data == CliInput::HELP      ) return;
    // *INDENT-ON*
}

CliInput readAndValidateParser(const ArgParser& parser)
{
    const auto modeString = parser.get(CliInput::MODE);
    CliInput::OperationMode mode = CliInput::OperationMode::INVALID;
    // *INDENT-OFF*
    if (modeString == CliInput::SIMULATION) mode = CliInput::OperationMode::SIMULATION;
    if (modeString == CliInput::TEMPLATE  ) mode = CliInput::OperationMode::TEMPLATE;
    if (modeString == CliInput::REMOTE    ) mode = CliInput::OperationMode::REMOTE;
    if (modeString == CliInput::HELP      ) mode = CliInput::OperationMode::HELP;
    // *INDENT-ON*

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
            throw CriticalAbort("Illegal State: operation mode = "s + modeString);
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
