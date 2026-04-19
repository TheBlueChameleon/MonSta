#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <filesystem>
#include <set>
#include <string>

struct HostApi;

namespace EngineBase
{
    extern std::set<std::string> supportedFeatures;

    extern bool abnormalTerminationRequest;

    extern bool overwriteFiles;
    extern bool createDirectories;
    extern bool dryMode;

    extern std::filesystem::path inputDirectory;
    extern std::filesystem::path outputDirectory;
    extern std::filesystem::path engine;

    extern HostApi* _hostApi;
}

#endif // GLOBALS_HPP
