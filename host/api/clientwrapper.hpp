#ifndef CLIENTWRAPPER_HPP
#define CLIENTWRAPPER_HPP

#include <filesystem>

#include <FeatureTags.hpp>
#include <Version.hpp>

class HostApi;

class ClientWrapper
{
    private:
        enum class FeatureCriticality {WARN, CRITICAL};
        using FeatureCheckParams = std::tuple<const char* const, std::string, FeatureCriticality>;
        const std::initializer_list<FeatureCheckParams> features =
        {
            {FEATURE_SIMULATIONMODE_V1_0, "simulation mode v1.0", FeatureCriticality::CRITICAL},
            {FEATURE_TEMPLATEMODE_V1_0,   "template mode v1.0",   FeatureCriticality::WARN}
        };

    private:
#ifdef _WIN32
        HINSTANCE handler;
#else
        void* handler = nullptr;
#endif
        const Version* _CLIENT_VERSION;
        const Version* _MIN_HOST_VERSION;
        const Version* _MAX_HOST_VERSION;

        bool (*_init)(HostApi* hostApi);
        bool (*_hasFeature)(const char* const featureTag);
        bool (*_hangUp)();
        void (*_terminateAbnormally)();

        template<typename T>
        void fetchCheckAndTransfer(T ClientWrapper::* offset, const char* const symbol);

        void loadEngine(const std::filesystem::path& enginePath);
        void extractSymbols();
        void assertVersionsCompatible();
        bool checkForFeatures(const FeatureCheckParams& featureDesc);

    protected:
        void* findSymbol(const char* const symbolName);
        bool init(HostApi* hostApi) const;
        bool hasFeature(const char* const featureTag);
        bool hangUp();

    public:
        ClientWrapper(const std::filesystem::path& enginePath);
        ~ClientWrapper();

        Version getClientVersion() const;
        Version getMinHostVersion() const;
        Version getMaxHostVersion() const;

        void terminateAbnormally();
};

#endif // CLIENTWRAPPER_HPP
