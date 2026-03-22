#ifndef ENTRYPOINT_HELP_HPP
#define ENTRYPOINT_HELP_HPP

#include <memory>

#include "../defs/basemodedefinition.hpp"

namespace Help
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // ENTRYPOINT_HELP_HPP
