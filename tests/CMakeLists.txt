cmake_minimum_required(VERSION 3.16)

# ============================================================================ #
# language definition

project(MonSta-Tests LANGUAGES
    CXX
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================ #
# framework

include(GoogleTest)

if (TARGET GTest::gtest_main)
    message("found gtest!")
else()
    message("no gtest!")
endif()

enable_testing()

# ============================================================================ #
# source file definitions

# ---------------------------------------------------------------------------- #
# Host

add_executable(Test-Host
    main-host.cpp
    csvservice/csvservicetest.hpp               csvservice/csvservicetest.cpp
    fileservice/fileservicetest.hpp             fileservice/fileservicetest.cpp
    fileservice/fileservicedatabasetest.hpp     fileservice/fileservicedatabasetest.cpp
    jsonservice/jsonservicedatabasetest.hpp     jsonservice/jsonservicedatabasetest.cpp
    jsonservice/jsonschemabuildertest.hpp       jsonservice/jsonschemabuildertest.cpp
    versionservice/versionservicetest.hpp       versionservice/versionservicetest.cpp
    serviceadapters/loggerserviceadapter.hpp    serviceadapters/loggerserviceadapter.cpp
)

target_include_directories(Test-Host
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(Test-Host
    GTest::gtest_main
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-RngService
    Host-VersionService
)

gtest_discover_tests(Test-Host)

# ---------------------------------------------------------------------------- #
# Gen1

add_executable(Test-Gen1
    main-gen1.cpp
    serviceadapters/loggerserviceadapter.hpp    serviceadapters/loggerserviceadapter.cpp
    engine-gen1/host/dlxinitialization.hpp      engine-gen1/host/dlxinitialization.cpp
)

target_include_directories(Test-Gen1
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(Test-Gen1
    GTest::gtest_main
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-RngService
    Host-VersionService
)

gtest_discover_tests(Test-Host)
