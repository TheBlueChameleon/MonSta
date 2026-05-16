#ifndef DLXINITIALIZATION_HPP
#define DLXINITIALIZATION_HPP

#include <filesystem>

#include "dlxservice/clientwrapper.hpp"

struct HostApi;

namespace DlxInitialization
{
    HostApi getServices();

    void initServices();

    ClientWrapper initEngine(const std::filesystem::path& enginePath);
}

#endif // DLXINITIALIZATION_HPP
