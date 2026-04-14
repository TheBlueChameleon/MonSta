#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP

#include <memory>

namespace OperationModes
{
    struct BaseModeDefinition;

    void run(const std::shared_ptr<const BaseModeDefinition>& runDefinition);
}

#endif // ENTRYPOINT_HPP
