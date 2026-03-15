#include <iostream>

#include <HostApi.hpp>

extern "C" {
    void foo()
    {
        std::cout << "about to foo thy bar." << std::endl;
    }

    void useHostLogger(HostApi* api)
    {
        api->logger->info("thy bar has been foo'd");
    }
}
