#include "../../api/loggerservice.hpp"

#include "../../defs/safecast.hpp"

#include "../../errors.hpp"

#include "entrypoint.hpp"

namespace RemoteMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        const RemoteModeDefinition& xDefs = RunDefinitionUtils::getAsRemoteModeDefinition(defs);

        LoggerService::info("Remote mode not implemented yet.");
        std::exit(0);
    }
}
