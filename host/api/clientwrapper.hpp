#ifndef CLIENTWRAPPER_HPP
#define CLIENTWRAPPER_HPP

#include <filesystem>
#include <set>

#include <ClientReturnCodes.hpp>
#include <FeatureTags.hpp>
#include <HostApi.hpp>
#include <Version.hpp>

#include "hostapiprovider.hpp"

class HostApi;

class ClientWrapper
{
    private:
        // ------------------------------------------------------------------ //
        // DyLib Handle

#ifdef _WIN32
        HINSTANCE handler;
#else
        void* handler = nullptr;
#endif

        // ------------------------------------------------------------------ //
        // Feature Requirements

        enum class FeatureCriticality {WARN, CRITICAL};
        using FeatureCheckParams = std::tuple<const char* const, std::string, FeatureCriticality>;

        const std::initializer_list<FeatureCheckParams> features =
        {
            {FEATURE_SIMULATIONMODE_V1_0, "simulation mode v1.0", FeatureCriticality::CRITICAL},
            {FEATURE_TEMPLATEMODE_V1_0,   "template mode v1.0",   FeatureCriticality::WARN}
        };

        // ------------------------------------------------------------------ //
        // Internal Logic

        template<typename T>
        void fetchCheckAndTransfer(T ClientWrapper::* offset, const char* const symbol);
        void* findSymbol(const char* const symbolName);

        void loadEngine(const std::filesystem::path& enginePath);
        void extractSymbols();
        bool checkForFeatures(const FeatureCheckParams& featureDesc);
        void initAndAssertCompatibility();

        // ------------------------------------------------------------------ //
        // State

        std::set<std::string> featureSet;
        HostApi               hostApi;

        const Version* _CLIENT_VERSION;
        const Version* _MIN_HOST_VERSION;
        const Version* _MAX_HOST_VERSION;

        ClientReturnCode(*_init)(HostApi* hostApi);
        ClientReturnCode(*_hangUp)();

        bool (*_hasFeature)(const char* const featureTag);
        void (*_terminateAbnormally)();

        ClientReturnCode(*_startTemplatesMode)();

        // ------------------------------------------------------------------ //
        // Private Interface

        ClientReturnCode init(HostApi* hostApi) const;
        ClientReturnCode hangUp();

        // ------------------------------------------------------------------ //
        // Public Interface
    public:
        ClientWrapper(
            const std::filesystem::path& enginePath,
            const HostApi&               hostApi = HostApiProvider::createHostApi()
        );
        ~ClientWrapper();

        ClientWrapper& operator=(const ClientWrapper&) = delete;
        ClientWrapper& operator=(ClientWrapper&&) = delete;

        const std::set<std::string>& getFeatureSet() const;
        bool hasFeature(const std::string_view featureTag);

        Version getClientVersion() const;
        Version getMinHostVersion() const;
        Version getMaxHostVersion() const;

        void terminateAbnormally();

        ClientReturnCode startTemplatesMode();
};

#endif // CLIENTWRAPPER_HPP
