#include <iostream>

#include "entrypoint.hpp"

#include "../defs/safecast.hpp"

namespace HelpMode
{
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

    void run(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        const HelpModeDefinition& xDefs = RunDefinitionUtils::getAsHelpModeDefinition(defs);
        showModeHelp(xDefs.target);
    }
}
