#include <iostream>

#include "cli/clihandler.hpp"

#include "filesystem/filewriterservice.hpp"

#include "operationmodes/help/entrypoint.hpp"
#include "operationmodes/remote/entrypoint.hpp"
#include "operationmodes/schemaExport/entrypoint.hpp"
#include "operationmodes/simulation/entrypoint.hpp"
#include "operationmodes/template/entrypoint.hpp"

#include "errors.hpp"

void run(const int argc, const char* const argv[])
{
    const CliInput cliInput = readCliInput(argc, argv);
    const std::shared_ptr<const BaseModeDefinition> runDefinition = unpackCliInput(cliInput);

    switch (runDefinition->mode)
    {
        case OperationMode::SIMULATION:
            SimulationMode::run(runDefinition);
            break;
        case OperationMode::TEMPLATE:
            TemplateMode::run(runDefinition);
            break;
        case OperationMode::SCHEMAEXPORT:
            SchemaExportMode::run(runDefinition);
            break;
        case OperationMode::REMOTE:
            RemoteMode::run(runDefinition);
            break;
        case OperationMode::HELP:
            HelpMode::run(runDefinition);
    }

    if (runDefinition->dryMode)
    {
        std::cout << "dry run summary:" << std::endl;
        for (const auto& info : FileWriterService::getCreatedFileInfo())
        {
            std::cout << (info.overwritten ? "overwritten " : "new file    ") << "\t" << info.filename.c_str() << std::endl;
        }
        if (FileWriterService::getCreatedFileInfo().empty())
        {
            std::cout << "-- none --" << std::endl;
        }
    }
}

int main(const int argc, const char* const argv[])
{
    try
    {
        run(argc, argv);
    }
    catch (const CriticalAbort& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (const IllegalStateException& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "This means <the dev> fucked up. Please report what you did to them with a stern look." << std::endl;
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
