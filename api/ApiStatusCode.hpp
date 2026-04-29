#ifndef API_STATUS_CODE_HPP
#define API_STATUS_CODE_HPP

#include <cstdint>

namespace ApiStatusCode
{
    enum ApiStatusCodes
    {
        SUCCESS,

        // low level errors
        CRITICAL_ABORT,
        INITIALIZATION_ERROR,
        ILLEGAL_STATE,
        INVALID_REQUEST,
        MULTIPLE_ERRORS,

        // service internal errors
        IO_ERROR,
        LOOKUP_ERROR,
        JSON_ERROR,
        CSV_ERROR,

        // invalid inputs
        INVALID_USER_INPUT,         // error by user
        ILLEGAL_ARGUMENT,           // error might be due to internal message passing
        MISSING_PARAMETER,
        NOT_IMPLEMENTED,

        // use this as base value for own error code enums
        USERDEFINED_ERROR = 1000
    };
}

#endif // API_STATUS_CODE_HPP
