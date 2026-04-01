#ifndef ENTRYPOINT_HELP_HPP
#define ENTRYPOINT_HELP_HPP

#include <memory>

struct HelpModeDefinition;

namespace HelpMode
{
    void run(const HelpModeDefinition& defs);
}

#endif // ENTRYPOINT_HELP_HPP
