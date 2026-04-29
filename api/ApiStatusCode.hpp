#ifndef API_STATUS_CODE_HPP
#define API_STATUS_CODE_HPP

#include <cstdint>

namespace ApiStatusCode
{
    enum ApiStatusCodes
    {
        SUCCESS,
        CRITICAL_ABORT,

        INVALID_USER_INPUT,

        HOST_INITIALIZATION_ERROR,
        INVALID_REQUEST_BY_HOST,
        ILLEGAL_HOST_STATE,
        IO_ERROR,
        LOOKUP_ERROR,
        JSON_ERROR,
        CSV_ERROR,

        CLIENT_INITIALIZATION_ERROR,
        INVALID_REQUEST_BY_CLIENT,
        ILLEGAL_CLIENT_STATE,
    };
}

#endif // API_STATUS_CODE_HPP
