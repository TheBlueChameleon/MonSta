#include <iostream>

#include <HostApi.hpp>
#include "hostapiwrapper.hpp"
#include "logger.hpp"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

void loadAndCallSO()
{
    const auto enginePath = "./libEngine-Gen1.so";
    void* handler = nullptr;

    handler = dlopen(enginePath, RTLD_LAZY);

    if (!handler)
    {
        spdlog::critical("COULD NOT LOAD {}", enginePath);
        spdlog::critical(dlerror());
        return;
    }

    char* error = nullptr;
    auto* symbol = dlsym(handler, "foo");
    if ((error = dlerror()) != nullptr || !symbol)
    {
        spdlog::critical("COULD NOT FIND SYMBOL {}", "foo");
        spdlog::critical(error);
        return;
    }

    auto foo = reinterpret_cast<void(*)(void)>(symbol);

    foo();

    error = nullptr;
    symbol = dlsym(handler, "useHostLogger");
    if ((error = dlerror()) != nullptr || !symbol)
    {
        spdlog::critical("COULD NOT FIND SYMBOL {}", "useHostLogger");
        spdlog::critical(error);
        return;
    }


    auto useHostLogger = reinterpret_cast<void(*)(HostApi*)>(symbol);
    useHostLogger(HostApiWrapper::GetInstancePtr());

    dlclose(handler);
}

int main()
{
    HostApiWrapper::GetInstance().logger->info("foo thy bar");

    loadAndCallSO();
}
