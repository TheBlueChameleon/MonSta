#ifndef CLIENTWRAPPER_HPP
#define CLIENTWRAPPER_HPP

#include <filesystem>
#include <set>

#include <ApiStatusCode.hpp>
#include <CallingConventions.hpp>
#include <FeatureTags.hpp>
#include <HostApi.hpp>
#include <Version.hpp>

#include "hostapiprovider.hpp"

class HostApi;
struct TemplatesDefinition;

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

        bool(HOST_API_CALL* _init)(HostApi* hostApi);
        void(HOST_API_CALL* _hangUp)();

        bool (HOST_API_CALL* _hasFeature)(const char* const featureTag);
        void (HOST_API_CALL* _terminateAbnormally)();

        void (HOST_API_CALL* _setOverwrite)(const bool overwrite);
        void (HOST_API_CALL* _setCreateDirectories)(const bool createDirectories);
        void (HOST_API_CALL* _setDryMode)(const bool dryMode);

        void(HOST_API_CALL* _startTemplatesMode)();

        // ------------------------------------------------------------------ //
        // Private Interface

        bool init(HostApi* hostApi) const;
        void hangUp();

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

        void setOverwrite(const bool overwrite);
        void setCreateDirectories(const bool createDirectories);
        void setDryMode(const bool dryMode);

        void startTemplatesMode(const TemplatesDefinition& templatesDefinition);
};

#endif // CLIENTWRAPPER_HPP
