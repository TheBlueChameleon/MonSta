#ifndef CLIENTWRAPPER_HPP
#define CLIENTWRAPPER_HPP

#include <filesystem>

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
};

#endif // CLIENTWRAPPER_HPP
