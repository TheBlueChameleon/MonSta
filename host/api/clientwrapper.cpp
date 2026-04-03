#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <Version.hpp>

#include "constants.hpp"
#include "errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "versionservice/versionservice.hpp"

#include "clientwrapper.hpp"

#define FETCH(symbol) fetchCheckAndTransfer(&ClientWrapper::_##symbol, #symbol)

template<typename T>
void ClientWrapper::fetchCheckAndTransfer(T ClientWrapper::*offset, const char* const symbol)
{
    using targetPtr_t = std::remove_reference<decltype(this->*offset)>::type;
    targetPtr_t target = reinterpret_cast<targetPtr_t>(findSymbol(symbol));

    if (target == nullptr)
    {
        LoggerService::criticalF("COULD NOT EXTRACT FUNCTION {}", symbol);
        throw CriticalAbort();
    }
    else
    {
        LoggerService::traceF("  ... EXTRACTED {}", symbol);
    }

    this->*offset =target;
}

void* ClientWrapper::findSymbol(const char* const symbolName)
{
#ifdef _WIN32
    auto* symbol = reinterpret_cast<void*>(GetProcAddress(handler, symbolName));
    if (!symbol)
    {
        LoggerService::criticalF("COULD NOT FIND SYMBOL {}", symbolName);
        return nullptr;
    }
#else
    char* error = nullptr;
    auto* symbol = dlsym(handler, symbolName);
    if ((error = dlerror()) != nullptr || !symbol)
    {
        LoggerService::criticalF("COULD NOT FIND SYMBOL {}", symbolName);
        LoggerService::critical(error);
        return nullptr;
    }
#endif
    return symbol;
}

void ClientWrapper::loadEngine(const std::filesystem::__cxx11::path& enginePath)
{
    LoggerService::traceF("LOADING ENGINE FROM {}", enginePath.c_str());

#ifdef _WIN32
    handler = LoadLibrary(enginePath.c_str());
#else
    handler = dlopen(enginePath.c_str(), RTLD_LAZY);
#endif

    if (!handler)
    {
        LoggerService::criticalF("COULD NOT LOAD {}", enginePath.c_str());
        LoggerService::critical(dlerror());
        throw CriticalAbort();
    }

    LoggerService::trace("... SUCCESS!");
}

void ClientWrapper::extractSymbols()
{
    LoggerService::trace("EXTRACTING FUNCTIONS ...");

    FETCH(CLIENT_VERSION);
    FETCH(MIN_HOST_VERSION);
    FETCH(MAX_HOST_VERSION);

    FETCH(init);
    FETCH(hasFeature);
    FETCH(hangUp);
    FETCH(terminateAbnormally);
    FETCH(startTemplatesMode);

    LoggerService::trace("... SUCCESS!");
}

bool ClientWrapper::checkForFeatures(const FeatureCheckParams& featureDesc)
{
    const auto& [featureTag, description, criticality] = featureDesc;
    if (hasFeature(featureTag))
    {
        featureSet.emplace(featureTag);
        return true;
    }
    else
    {
        switch (criticality)
        {
            case ClientWrapper::FeatureCriticality::WARN:
                LoggerService::warnF("The feature '{}' is not supported by this client. Not all operations may be available.",
                                     description
                                    );
                return true;
            case ClientWrapper::FeatureCriticality::CRITICAL:
                LoggerService::criticalF("The critical feature '{}' is not supported by this client.",
                                         description
                                        );
                return false;
        }
        throw IllegalStateException("Unknown criticality level");
    }
}

void ClientWrapper::initAndAssertCompatibility()
{
    LoggerService::trace("ASSERTING VERSION COMPATIBILITY ...");

    const auto clientVersion = getClientVersion();

    LoggerService::traceF("  ... Client Version is {}", VersionService::to_string(clientVersion));
    LoggerService::traceF("  ... Host Version is   {}", VersionService::to_string(HOST_VERSION));

    if (HOST_VERSION < getMinHostVersion())
    {
        LoggerService::criticalF("Host Version is {} but at least Version {} is required for this client.",
                                 VersionService::to_string(HOST_VERSION),
                                 VersionService::to_string(getMinHostVersion())
                                );
        throw CriticalAbort("Incompatible Host Version");
    }
    if (HOST_VERSION > getMaxHostVersion())
    {
        LoggerService::criticalF("Host Version is {} but at least Version {} is required for this client.",
                                 VersionService::to_string(HOST_VERSION),
                                 VersionService::to_string(getMaxHostVersion())
                                );
        throw CriticalAbort("Incompatible Host Version");
    }

    LoggerService::trace("  ... Initializing client");
    const auto connectionStatus = init(&hostApi);
    if (connectionStatus != ClientReturnCode::SUCCESS)
    {
        LoggerService::critical("Client refused the connection!");
        throw ClientSideError(connectionStatus);
    }
    LoggerService::trace("  ... Client accepted connection.");

    bool allCriticalFeaturesAvailable = true;
    for (const auto& feature: features)
    {
        allCriticalFeaturesAvailable &= checkForFeatures(feature);
    }
    if (!allCriticalFeaturesAvailable)
    {
        throw ClientSideError("Critical feature not implemented by client");
    }

    LoggerService::trace("  ... Version check successful.");

    LoggerService::trace("... SUCCESS!");
}

ClientWrapper::ClientWrapper(
    const std::filesystem::path& enginePath,
    const HostApi&               hostApi
) :
    hostApi(hostApi)
{
    LoggerService::debug("BOOTING ENGINE WRAPPER");

    loadEngine(enginePath);
    extractSymbols();
    initAndAssertCompatibility();

    LoggerService::debug("... DONE");
}

ClientWrapper::~ClientWrapper()
{
    auto operationStatus = hangUp();
    if (operationStatus != ClientReturnCode::SUCCESS)
    {
        LoggerService::critical("Error in shutdwon process of client");
        LoggerService::criticalF("Error Code: {}", static_cast<int>(operationStatus));
        std::exit(-1);
    }

    if (handler)
    {
#ifdef _WIN32
        FreeLibrary(handler);
#else
        dlclose(handler);
#endif
    }
}

const std::set<std::string>& ClientWrapper::getFeatureSet() const
{
    return featureSet;
}

ClientReturnCode ClientWrapper::init(HostApi* hostApi) const
{
    return _init(hostApi);
}

ClientReturnCode ClientWrapper::hangUp()
{
    return _hangUp();
}

bool ClientWrapper::hasFeature(const std::string_view featureTag)
{
    return _hasFeature(featureTag.data());
}

Version ClientWrapper::getClientVersion() const
{
    return *_CLIENT_VERSION;
}

Version ClientWrapper::getMinHostVersion() const
{
    return *_MIN_HOST_VERSION;
}

Version ClientWrapper::getMaxHostVersion() const
{
    return *_MAX_HOST_VERSION;
}

void ClientWrapper::terminateAbnormally()
{
    _terminateAbnormally();
}

ClientReturnCode ClientWrapper::startTemplatesMode()
{
    return _startTemplatesMode();
}
