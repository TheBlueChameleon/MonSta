#ifndef LOGGERSERVICE_DLX_HPP
#define LOGGERSERVICE_DLX_HPP

#include <CallingConventions.hpp>

namespace LoggerService
{
    void HOST_API_CALL trace_dlx(const char* const msg);
    void HOST_API_CALL debug_dlx(const char* const msg);
    void HOST_API_CALL info_dlx(const char* const msg);
    void HOST_API_CALL warn_dlx(const char* const msg);
    void HOST_API_CALL error_dlx(const char* const msg);
    void HOST_API_CALL critical_dlx(const char* const msg);
}

#endif // LOGGERSERVICE_DLX_HPP
