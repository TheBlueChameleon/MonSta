#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <set>
#include <string>

struct HostApi;

namespace Globals
{
    extern HostApi* hostApi;

    extern std::set<std::string> supportedFeatures;
}

#endif // GLOBALS_HPP
