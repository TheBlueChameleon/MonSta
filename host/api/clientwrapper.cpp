#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <spdlog/spdlog.h>

#include <Version.hpp>

#include "clientwrapper.hpp"
#include "../constants.hpp"
#include "../errors.hpp"
#include "hostapiwrapper.hpp"
#include "versionutils.hpp"

#define FETCH(symbol) fetchCheckAndTransfer(&ClientWrapper::_##symbol, #symbol)

template<typename T>
void ClientWrapper::fetchCheckAndTransfer(T ClientWrapper::*offset, const char* const symbol)
{
    using targetPtr_t = std::remove_reference<decltype(this->*offset)>::type;
    targetPtr_t target = reinterpret_cast<targetPtr_t>(findSymbol(symbol));

    if (target == nullptr)
    {
        spdlog::critical("COULD NOT EXTRACT FUNCTION {}", symbol);
        throw CriticalAbort();
    }
    else
    {
        spdlog::trace("  ... EXTRACTED {}", symbol);
    }

    this->*offset =target;
}

void ClientWrapper::loadEninge(const std::filesystem::__cxx11::path& enginePath)
{
    spdlog::trace("LOADING ENGINE FROM {}", enginePath.c_str());

#ifdef _WIN32
    handler = LoadLibrary(enginePath.c_str());
#else
    handler = dlopen(enginePath.c_str(), RTLD_LAZY);
#endif

    if (!handler)
    {
        spdlog::critical("COULD NOT LOAD {}", enginePath.c_str());
        spdlog::critical(dlerror());
        throw CriticalAbort();
    }

    spdlog::trace("... SUCCESS!");
}

void ClientWrapper::extractFunctions()
{
    spdlog::trace("EXTRACTING FUNCTIONS ...");

    FETCH(getClientVersion);
    FETCH(connectToHost);

    spdlog::trace("... SUCCESS!");
}

void ClientWrapper::assertVersionsBothSides()
{
    spdlog::trace("ASSERTING VERSION COMPATIBILITY ...");

    const auto clientVersion = getClientVersion();

    spdlog::trace("  ... Client Version is {}", VersionUtils::to_string(clientVersion));
    spdlog::trace("  ... Host Version is {}", VersionUtils::to_string(HOST_VERSION));

    if (clientVersion < MIN_CLIENT_VERSION)
    {
        spdlog::critical("Client Version is {} but at least Version {} is required for this host.",
                         VersionUtils::to_string(clientVersion),
                         VersionUtils::to_string(HOST_VERSION)
                        );
        throw CriticalAbort();
    }

    const auto connected = connectToHost(HostApiWrapper::GetInstancePtr());
    if (connected)
    {
        spdlog::trace("  ... Client accepted connection.");
    }
    else
    {
        spdlog::critical("Client refused the connection.");
        throw CriticalAbort();
    }

    spdlog::trace("... SUCCESS!");
}

void* ClientWrapper::findSymbol(const char* const symbolName)
{
#ifdef _WIN32
    auto* symbol = reinterpret_cast<void*>(GetProcAddress(hGetProcIDDLL, symbolName));
    if (!symbol)
    {
        spdlog::critical("COULD NOT FIND SYMBOL {}", symbolName);
    }
#else
    char* error = nullptr;
    auto* symbol = dlsym(handler, symbolName);
    if ((error = dlerror()) != nullptr || !symbol)
    {
        spdlog::critical("COULD NOT FIND SYMBOL {}", symbolName);
        spdlog::critical(error);
        return nullptr;
    }
#endif
    return symbol;
}

bool ClientWrapper::connectToHost(HostApi* hostApi) const
{
    return _connectToHost(hostApi);
}

ClientWrapper::ClientWrapper(const std::filesystem::path& enginePath)
{
    spdlog::debug("BOOTING ENGINE WRAPPER");

    loadEninge(enginePath);
    extractFunctions();
    assertVersionsBothSides();

    spdlog::debug("... DONE");
}

ClientWrapper::~ClientWrapper()
{
    if (handler)
    {
#ifdef _WIN32
        FreeLibrary(handler);
#else
        dlclose(handler);
#endif
    }
}

Version ClientWrapper::getClientVersion() const
{
    return _getClientVersion();
}
