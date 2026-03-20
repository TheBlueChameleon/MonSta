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
        const Version* _CLIENT_VERSION;
        const Version* _MIN_HOST_VERSION;
        const Version* _MAX_HOST_VERSION;

        bool(*_init)(HostApi* hostApi);
        bool(*_hangUp)();

        template<typename T>
        void fetchCheckAndTransfer(T ClientWrapper::* offset, const char* const symbol);

        void loadEngine(const std::filesystem::path& enginePath);
        void extractSymbols();
        void assertVersionsCompatible();

    protected:
        void* findSymbol(const char* const symbolName);
        bool init(HostApi* hostApi) const;
        bool hangUp();

    public:
        ClientWrapper(const std::filesystem::path& enginePath);
        ~ClientWrapper();

        Version getClientVersion() const;
        Version getMinHostVersion() const;
        Version getMaxHostVersion() const;
};

#endif // CLIENTWRAPPER_HPP
