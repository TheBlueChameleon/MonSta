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
# Utils

# ............................................................................ #
# Utils-Generic

# TODO: extract runWithCapturedStdErr from ClientApiTest

# ............................................................................ #
# Utils-Host

add_library(Test-Utils-Host
    host/serviceadapters/loggerserviceadapter.hpp   host/serviceadapters/loggerserviceadapter.cpp
    host/serviceadapters/fileserviceadapter.hpp     host/serviceadapters/fileserviceadapter.cpp
)

target_include_directories(Test-Utils-Host
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(Test-Utils-Host
    nlohmann_json::nlohmann_json
    spdlog
    Api-Headers
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-RngService
    Host-VersionService
)

# ............................................................................ #
# Utils-Engine

add_library(Test-Utils-Engine
    engines/util/dlxinitialization.hpp      engines/util/dlxinitialization.cpp
)

target_include_directories(Test-Utils-Engine
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${CMAKE_SOURCE_DIR}/tests
    PRIVATE ${CMAKE_SOURCE_DIR}/engines
    PRIVATE ${json_SOURCE_DIR}/include
)

target_link_libraries(Test-Utils-Engine
    Api-Headers
    Host-DlxService
)

set_target_properties(Test-Utils-Engine PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------- #
# Host

add_executable(Test-Host
    host/main.cpp
    host/csvservice/csvservicetest.hpp              host/csvservice/csvservicetest.cpp
    host/fileservice/fileservicetest.hpp            host/fileservice/fileservicetest.cpp
    host/fileservice/fileservicedatabasetest.hpp    host/fileservice/fileservicedatabasetest.cpp
    host/jsonservice/jsonservicedatabasetest.hpp    host/jsonservice/jsonservicedatabasetest.cpp
    host/jsonservice/jsonschemabuildertest.hpp      host/jsonservice/jsonschemabuildertest.cpp
    host/versionservice/versionservicetest.hpp      host/versionservice/versionservicetest.cpp
)

target_include_directories(Test-Host
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${CMAKE_SOURCE_DIR}/tests/host
)

target_link_libraries(Test-Host
    GTest::gtest_main
    Api-Headers
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-RngService
    Host-VersionService
    Test-Utils-Host
)

gtest_discover_tests(Test-Host)

# ---------------------------------------------------------------------------- #
# Engine-Base

add_executable(Test-Base
    engines/base/main.cpp
    engines/base/clientapitest.hpp   engines/base/clientapitest.cpp
)

target_include_directories(Test-Base
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/engines
    PRIVATE ${CMAKE_SOURCE_DIR}/tests/engines
)

target_link_libraries(Test-Base
    GTest::gtest_main
    Api-Headers
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-RngService
    Host-VersionService
    Engine-Base
    Test-Utils-Host
    Test-Utils-Engine
)

gtest_discover_tests(Test-Base)

# ---------------------------------------------------------------------------- #
# Gen1

add_executable(Test-Gen1
    engines/gen1/main.cpp
    engines/gen1/templatesmodetest.hpp  engines/gen1/templatesmodetest.cpp
)

target_include_directories(Test-Gen1
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/engines/engine-base
    PRIVATE ${CMAKE_SOURCE_DIR}/engines/engine-gen1
    PRIVATE ${CMAKE_SOURCE_DIR}/tests/engines
    PRIVATE ${CMAKE_SOURCE_DIR}/tests/host
)

target_link_libraries(Test-Gen1
    GTest::gtest_main
    Api-Headers
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-RngService
    Host-VersionService
    Engine-Gen1
    Test-Utils-Host
    Test-Utils-Engine
)

gtest_discover_tests(Test-Host)
