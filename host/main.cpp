#include <iostream>

#include "api/clientwrapper.hpp"
#include "api/hostapiwrapper.hpp"

#include "cli/clihandler.hpp"

#include "defs/helpmodedefinition.hpp"
#include "defs/simulationmodedefinition.hpp"

#include "constants.hpp"
#include "errors.hpp"

int main(const int argc, const char* const argv[])
{
    try
    {
        const CliInput cliInput = readCliInput(argc, argv);
        const std::shared_ptr<const BaseModeDefinition> defs = unpackCliInput(cliInput);

        switch (defs->mode)
        {
            case OperationMode::SIMULATION:
                break;
            case OperationMode::TEMPLATE:
                break;
            case OperationMode::REMOTE:
                break;
            case OperationMode::HELP:
                const auto ptr = std::dynamic_pointer_cast<const HelpModeDefinition>(defs);
                const auto mode = ptr->target;
                showModeHelp(mode);
                break;
        }

        //ClientWrapper cw("./build-Desktop-Debug/libEngine-Gen1.so");
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
