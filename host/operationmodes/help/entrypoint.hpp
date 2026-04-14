#ifndef ENTRYPOINT_HELP_HPP
#define ENTRYPOINT_HELP_HPP

#include <memory>

namespace OperationModes
{
    struct HelpModeDefinition;
}

namespace HelpMode
{
    void run(const OperationModes::HelpModeDefinition& defs);
}

#endif // ENTRYPOINT_HELP_HPP
