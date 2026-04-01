#ifndef ENTRYPOINT_REMOTE_HPP
#define ENTRYPOINT_REMOTE_HPP

#include <memory>

struct RemoteModeDefinition;

namespace RemoteMode
{
    void run(const RemoteModeDefinition& defs);
}

#endif // ENTRYPOINT_REMOTE_HPP
