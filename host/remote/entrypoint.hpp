#ifndef ENTRYPOINT_REMOTE_HPP
#define ENTRYPOINT_REMOTE_HPP

#include <memory>

#include "../defs/basemodedefinition.hpp"

namespace RemoteMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // ENTRYPOINT_REMOTE_HPP
