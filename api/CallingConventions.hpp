#ifndef CALLINGCONVENTIONS_HPP
#define CALLINGCONVENTIONS_HPP

#ifdef _WIN32
    #define HOST_API_CALL __cdecl
    #define HOST_API_EXPORT extern "C" __declspec(dllexport)
    #define HOST_API_IMPORT extern "C" __declspec(dllimport)
#else
    #define HOST_API_CALL
    #define HOST_API_EXPORT extern "C"
    #define HOST_API_IMPORT extern "C"
#endif

#endif // CALLINGCONVENTIONS_HPP
