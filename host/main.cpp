#include <iostream>

#include "cli/clihandler.hpp"

#include "operationmodes/entrypoint.hpp"
#include "operationmodes/shared/schemavalidationconstants.hpp"

#include "errors.hpp"

void registerSchemas()
{
    OperationModes::registerSchemaSimulation();
    OperationModes::registerSchemaTemplate();
}

void run(const int argc, const char* const argv[])
{
    const CliInput cliInput = readCliInput(argc, argv);
    const std::shared_ptr<const BaseModeDefinition> runDefinition = unpackCliInput(cliInput);

    OperationModes::run(runDefinition);
}

int main(const int argc, const char* const argv[])
{
    // playground();
    // std::exit(0);

    try
    {
        registerSchemas();
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
        std::cerr << "This means <the host dev> fucked up." << std::endl;
        std::cerr << "Please report to them what you were doing when this error occurred and give them a stern look." << std::endl;
        return -1;
    }
    catch (const ClientSideError& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "This means <the plugin dev> fucked up." << std::endl;
        std::cerr << "Please report to them what you were doing when this error occurred and give them a stern look." << std::endl;
        return -1;
    }

    return 0;
}
