#include <iostream>

#include <HostApi.hpp>

#include "api/clientwrapper.hpp"
#include "errors.hpp"
#include "inputs.hpp"
#include "api/hostapiwrapper.hpp"
#include "api/logger.hpp"

#include "cli/clihandler.hpp"

Inputs getInputs()
{
    return Inputs();
}

int main(const int argc, const char* const argv[])
{
    try
    {
        HostApiWrapper::getLogger().makeDefault();

        const auto cliInput = parseCliInput(argc, argv);
        switch (cliInput.mode)
        {
            case CliInput::OperationMode::SIMULATION:
                break;
            case CliInput::OperationMode::TEMPLATE:
                break;
            case CliInput::OperationMode::REMOTE:
                break;
            case CliInput::OperationMode::HELP:
                showModeHelp(cliInput.data);
                break;
            case CliInput::OperationMode::INVALID:
                throw CriticalAbort("Invalid operation mode");
        }

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
