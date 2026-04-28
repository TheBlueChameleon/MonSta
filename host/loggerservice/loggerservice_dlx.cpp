#include "loggerservice.hpp"
#include "loggerservice_dlx.hpp"

namespace LoggerService
{
    void HOST_API_CALL trace_dlx(const char* const msg)
    {
        trace(msg);
    }

    void HOST_API_CALL debug_dlx(const char* const msg)
    {
        debug(msg);
    }

    void HOST_API_CALL info_dlx(const char* const msg)
    {
        info(msg);
    }

    void HOST_API_CALL warn_dlx(const char* const msg)
    {
        warn(msg);
    }

    void HOST_API_CALL error_dlx(const char* const msg)
    {
        error(msg);
    }

    void HOST_API_CALL critical_dlx(const char* const msg)
    {
        critical(msg);
    }
}
