#include <iostream>

#include <HostApi.hpp>
#include "clientwrapper.hpp"
#include "hostapiwrapper.hpp"
#include "logger.hpp"

// void exportToTest_Version()
// {
//     Version ve1(1,2,3,4);
//     Version ve2(1,2,3,4);
//     Version vl1(1,2,3,0);
//     Version vl2(1,2,0,5);
//     Version vl3(1,0,4,5);
//     Version vl4(0,3,4,5);

//     std::cout << ve1 << " == " << ve2 << ": " << (ve1 == ve2) << std::endl;

//     std::cout << ve1 << " <  " << vl1 << ": " << (ve1 < vl1) << std::endl;
//     std::cout << ve1 << " <  " << vl2 << ": " << (ve1 < vl2) << std::endl;
//     std::cout << ve1 << " <  " << vl3 << ": " << (ve1 < vl3) << std::endl;
//     std::cout << ve1 << " <  " << vl4 << ": " << (ve1 < vl4) << std::endl;

//     std::cout << ve1 << " >  " << vl1 << ": " << (ve1 > vl1) << std::endl;
//     std::cout << ve1 << " >  " << vl2 << ": " << (ve1 > vl2) << std::endl;
//     std::cout << ve1 << " >  " << vl3 << ": " << (ve1 > vl3) << std::endl;
//     std::cout << ve1 << " >  " << vl4 << ": " << (ve1 > vl4) << std::endl;
// }

int main()
{
    HostApiWrapper::getLogger().makeDefault();

    ClientWrapper cw("./libEngine-Gen1.so");
}
