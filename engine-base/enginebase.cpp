#include <ClientApi.hpp>

#include "services/errorservice.hpp"

#include "enginebase.hpp"
#include "errors.hpp"

namespace EngineBase
{
    void handleException(const EngineError& e)
    {
        ErrorService::setError(e.getErrorCode(), e.what());
        terminateAbnormally();
    }
}
