#ifndef CLIENTWRAPPER_HPP
#define CLIENTWRAPPER_HPP

#include <filesystem>

#include <HostApi.hpp>
#include <Version.hpp>

class ClientWrapper
{
    private:
#ifdef _WIN32
        HINSTANCE handler;
#else
        void* handler = nullptr;
#endif

        Version(*_getClientVersion)();
        bool(*_connectToHost)(HostApi* hostApi);

        template<typename T>
        void fetchCheckAndTransfer(T ClientWrapper::* offset, const char* const symbol);

        void loadEninge(const std::filesystem::path& enginePath);
        void extractFunctions();
        void assertVersionsBothSides();

    protected:
        void* findSymbol(const char* const symbolName);
        bool connectToHost(HostApi* hostApi) const;

    public:
        ClientWrapper(const std::filesystem::path& enginePath);
        ~ClientWrapper();

        Version getClientVersion() const;
};

#endif // CLIENTWRAPPER_HPP
