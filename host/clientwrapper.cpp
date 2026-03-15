#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <spdlog/spdlog.h>

#include "clientwrapper.hpp"
#include "errors.hpp"

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

void ClientWrapper::assertVersion()
{

}

void ClientWrapper::extractFunctions()
{
    spdlog::trace("EXTRACTING FUNCTIONS ...");

    FETCH(getClientVersion);
    FETCH(connectToHost);

    spdlog::trace("... SUCCESS!");
}

ClientWrapper::ClientWrapper(const std::filesystem::path& enginePath)
{
    spdlog::debug("BOOTING ENGINE WRAPPER");

    loadEninge(enginePath);
    assertVersion();
    extractFunctions();

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

Version ClientWrapper::getClientVersion() const
{
    return _getClientVersion();
}

void ClientWrapper::connectToHost(HostApi* hostApi) const
{

}
