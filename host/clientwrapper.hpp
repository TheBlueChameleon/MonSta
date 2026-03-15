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
        void(*_connectToHost)(HostApi* hostApi);

        template<typename T>
        void fetchCheckAndTransfer(T ClientWrapper::* offset, const char* const symbol);

        void loadEninge(const std::filesystem::path& enginePath);
        void assertVersion();
        void extractFunctions();

    public:
        ClientWrapper(const std::filesystem::path& enginePath);
        ~ClientWrapper();

        void* findSymbol(const char* const symbolName);

        Version getClientVersion() const;
        void connectToHost(HostApi* hostApi) const;
};

#endif // CLIENTWRAPPER_HPP
