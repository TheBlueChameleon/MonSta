#include "globals.hpp"

namespace Globals
{
    HostApi* _hostApi;

    std::set<std::string> supportedFeatures = {};

    bool abnormalTerminationRequest = false;
}
