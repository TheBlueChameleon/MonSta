#ifndef CATCHMACROS_HPP
#define CATCHMACROS_HPP

#include <exception>

#include <ApiStatusCode.hpp>

#include "errorservice/errorservice.hpp"

#define CATCH_CLIENT_REQUEST_ERROR(errorValue) \
    catch (const ClientRequestError& e) { \
        ErrorService::setError( e.getErrorCode(), \
                                e.what() \
                              ); \
        return errorValue; \
    }

#define CATCH_LOOKUP_ERROR(errorValue) \
    catch (const LookupError& e) { \
        ErrorService::setError( ApiStatusCode::LOOKUP_ERROR, \
                                e.what() \
                              ); \
        return errorValue; \
    }

#define CATCH_JSON_ERROR(errorValue) \
    catch (const nlohmann::ordered_json::exception& e) { \
        ErrorService::setError( ApiStatusCode::JSON_ERROR, \
                                e.what() \
                              ); \
        return errorValue; \
    }

#define CATCH_STD_EXCEPTION(errorValue) \
    catch (const std::exception& e) { \
        ErrorService::setError( ApiStatusCode::CRITICAL_ABORT, \
                                e.what() \
                              ); \
        return errorValue; \
    }

#endif // CATCHMACROS_HPP
