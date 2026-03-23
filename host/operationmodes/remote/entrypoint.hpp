#ifndef ENTRYPOINT_REMOTE_HPP
#define ENTRYPOINT_REMOTE_HPP

#include <memory>

struct BaseModeDefinition;

namespace RemoteMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // ENTRYPOINT_REMOTE_HPP
