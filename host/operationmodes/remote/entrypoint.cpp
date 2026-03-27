#include "errors.hpp"

#include "logging/loggerservice.hpp"

#include "operationmodes/safecast.hpp"

#include "entrypoint.hpp"
#include "remoterundefinition.hpp"

namespace RemoteMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        const RemoteModeDefinition& xDefs = RunDefinitionUtils::getAsRemoteModeDefinition(defs);

        LoggerService::info("Remote mode not implemented yet.");
        std::exit(0);
    }
}
