#include "errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/utils.hpp"

#include "entrypoint.hpp"
#include "remoterundefinition.hpp"

namespace RemoteMode
{
    void run(const RemoteModeDefinition& defs)
    {
        LoggerService::info("Remote mode not implemented yet.");
        std::exit(0);
    }
}
