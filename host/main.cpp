#include <iostream>

#include <HostApi.hpp>
#include "clientwrapper.hpp"
#include "hostapiwrapper.hpp"
#include "logger.hpp"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

int main()
{
    HostApiWrapper::GetInstance().logger->info("foo thy bar");

    ClientWrapper cw("./libEngine-Gen1.so");
    std::cout << cw.getClientVersion().minor << std::endl;
}
