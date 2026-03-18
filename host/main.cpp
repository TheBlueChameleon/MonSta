#include <fstream>
#include <iostream>
#include <string>
using namespace std::string_literals;

#include <json.hpp>
#include <json-schema.hpp>

#include <HostApi.hpp>

#include "api/clientwrapper.hpp"
#include "api/hostapiwrapper.hpp"
#include "api/logger.hpp"

#include "cli/clihandler.hpp"

#include "defs/simulationinputs.hpp"

#include "constants.hpp"
#include "errors.hpp"

const nlohmann::json readJsonFile(const std::filesystem::path& source)
{
    using Json = nlohmann::json;

    try
    {
        std::ifstream hFile(source);
        Json data = Json::parse(hFile);
        return data;
    }
    catch (const Json::parse_error& err)
    {
        throw CriticalAbort(
            "Error parsing JSON file '"s + source.c_str() + "'\n" +
            err.what()
        );
    }
}

void validateJsonAgainstJson(const nlohmann::json& data, const nlohmann::json& schema, const std::string& origin)
{
    using Json = nlohmann::json;
    using JsonValidator = nlohmann::json_schema::json_validator;

    JsonValidator validator;
    try
    {
        validator.set_root_schema(schema);
    }
    catch (const std::invalid_argument& e)
    {
        throw CriticalAbort(
            "Invalid state of simulation schema:\n"s +
            e.what()
        );
    }

    try
    {
        validator.validate(data);
    }
    catch (const std::invalid_argument& e)
    {
        throw CriticalAbort(
            "JSON data from '"s + origin + "' are invalid:\n" +
            e.what()
        );

        std::cerr << "Validation failed, here is why: " << e.what() << "\n";
    }
}

void handleSimulationInput(const std::filesystem::path& source)
{
    using Json = nlohmann::json;
    using JsonValidator = nlohmann::json_schema::json_validator;

    Json data = readJsonFile(source);
    validateJsonAgainstJson(data, SCHEMA_SIMULATION, source.c_str());

    std::cout << SCHEMA_SIMULATION << std::endl;
}

void handleTemplateInput(const std::filesystem::path& source)
{

}

void handleRemoteInput(const std::string& socket)
{
    throw CriticalAbort("Remote System: Not Implemented yet");
}

void handleCliInput(const CliInput& cliInput)
{
    switch (cliInput.mode)
    {
        case CliInput::OperationMode::SIMULATION:
            handleSimulationInput(cliInput.data);
            break;
        case CliInput::OperationMode::TEMPLATE:
            handleTemplateInput(cliInput.data);
            break;
        case CliInput::OperationMode::REMOTE:
            handleRemoteInput(cliInput.data);
            break;
        case CliInput::OperationMode::HELP:
            showModeHelp(cliInput.data);
            break;
        case CliInput::OperationMode::INVALID:
            throw CriticalAbort("Invalid operation mode");
    }
}

int main(const int argc, const char* const argv[])
{
    try
    {
        HostApiWrapper::getLogger().makeDefault();

        const auto cliInput = parseCliInput(argc, argv);
        handleCliInput(cliInput);

        //HostApiWrapper::getLogger().setLogFile("foo.log");

        ClientWrapper cw("./build-Desktop-Debug/libEngine-Gen1.so");
    }
    catch (const CriticalAbort& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}


// void exportToTest_Version()
// {
//     Version ve1(1,2,3,4);
//     Version ve2(1,2,3,4);
//     Version vl1(1,2,3,0);
//     Version vl2(1,2,0,5);
//     Version vl3(1,0,4,5);
//     Version vl4(0,3,4,5);

//     std::cout << ve1 << " == " << ve2 << ": " << (ve1 == ve2) << std::endl;

//     std::cout << ve1 << " <  " << vl1 << ": " << (ve1 < vl1) << std::endl;
//     std::cout << ve1 << " <  " << vl2 << ": " << (ve1 < vl2) << std::endl;
//     std::cout << ve1 << " <  " << vl3 << ": " << (ve1 < vl3) << std::endl;
//     std::cout << ve1 << " <  " << vl4 << ": " << (ve1 < vl4) << std::endl;

//     std::cout << ve1 << " >  " << vl1 << ": " << (ve1 > vl1) << std::endl;
//     std::cout << ve1 << " >  " << vl2 << ": " << (ve1 > vl2) << std::endl;
//     std::cout << ve1 << " >  " << vl3 << ": " << (ve1 > vl3) << std::endl;
//     std::cout << ve1 << " >  " << vl4 << ": " << (ve1 > vl4) << std::endl;
// }
