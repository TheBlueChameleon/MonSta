#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <set>
#include <string>

struct HostApi;

namespace Globals
{
    extern std::set<std::string> supportedFeatures;

    extern bool abnormalTerminationRequest;
}

#endif // GLOBALS_HPP
