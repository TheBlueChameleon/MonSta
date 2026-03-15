#include <iostream>

#include <HostApi.hpp>
#include <Version.hpp>

extern "C" {
    void foo()
    {
        std::cout << "about to foo thy bar." << std::endl;
    }

    void useHostLogger(HostApi* api)
    {
        api->logger->info("thy bar has been foo'd");
    }

    Version getClientVersion()
    {
        return Version(0,1,0,0);
    }
}
