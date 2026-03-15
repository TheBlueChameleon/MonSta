#include <iostream>

#include <HostAPI.hpp>

extern "C" {
    void foo()
    {
        std::cout << "about to foo thy bar." << std::endl;
    }

    void useHostLogger(HostAPI* api)
    {
        api->logger->info("thy bar has been foo'd");
    }
}
