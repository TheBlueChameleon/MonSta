#include "globals.hpp"

namespace EngineBase
{
    HostApi* _hostApi;

    std::set<std::string> supportedFeatures = {};

    bool abnormalTerminationRequest = false;

    bool overwriteFiles = false;
    bool createDirectories = false;
    bool dryMode = false;
}
