#ifndef ENTRYPOINT_REMOTE_HPP
#define ENTRYPOINT_REMOTE_HPP

#include <memory>

namespace OperationModes
{
    struct RemoteModeDefinition;
}

namespace RemoteMode
{
    void run(const OperationModes::RemoteModeDefinition& defs);
}

#endif // ENTRYPOINT_REMOTE_HPP
