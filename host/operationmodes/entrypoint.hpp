#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP

#include <memory>

struct BaseModeDefinition;

namespace OperationModes
{
    void run(const std::shared_ptr<const BaseModeDefinition>& runDefinition);
}

#endif // ENTRYPOINT_HPP
