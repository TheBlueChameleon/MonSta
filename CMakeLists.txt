cmake_minimum_required(VERSION 3.25)

include(FetchContent)
include(CMakePrintHelpers)

# ============================================================================ #
# language definition

project(MonSta LANGUAGES
    CXX
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================ #
# external dependencies

set(JSON_BuildTests OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # For Windows: Prevent overriding the parent project's compiler/linker settings
set(nlohmann_json_VERSION "v3.12.0")

FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse
  GIT_TAG "v3.2"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
  SYSTEM
)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG "v3.12.0"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
  SYSTEM
)
FetchContent_Declare(
  json-schema-validator
  GIT_REPOSITORY https://github.com/pboettch/json-schema-validator
  GIT_TAG "2.4.0"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
  SYSTEM
)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG        "v1.15.3"
    GIT_SHALLOW    true
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG        "v1.17.0"
)

# more `FetchContent_Declare`s (if any). They should all be declared
# before any calls to FetchContent_Make_available (see docs for why).

FetchContent_MakeAvailable(argparse)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(json-schema-validator)
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(googletest)


# ============================================================================ #
# source file definitions

# ---------------------------------------------------------------------------- #
# Shared

set(apiHeaders
    api/ClientApi.hpp
    api/HostApi.hpp
    api/IFileService.hpp
    api/ILoggerService.hpp
    api/IJsonService.hpp
    api/IVersionService.hpp
    api/IMatchDefinitions.hpp
    api/Version.hpp
)

# ---------------------------------------------------------------------------- #
# Main App

# ............................................................................ #
# FileService

add_library(Host-FileService STATIC
    host/fileservice/debugstream.hpp
    host/fileservice/fileservice.hpp            host/fileservice/fileservice.cpp
    host/fileservice/fileservicedatabase.hpp    host/fileservice/fileservicedatabase.cpp
    host/fileservice/fileserviceoperations.hpp  host/fileservice/fileserviceoperations.cpp
    host/fileservice/nullstream.hpp
    host/fileservice/stdoutstream.hpp           host/fileservice/stdoutstream.cpp
    host/fileservice/synchronizedostream.hpp    host/fileservice/synchronizedostream.cpp
    host/fileservice/types.hpp
)

target_include_directories(Host-FileService
    PUBLIC host
    PUBLIC api
)

# ............................................................................ #
# JsonService

add_library(Host-JsonService STATIC
    host/jsonservice/jsonservice.hpp            host/jsonservice/jsonservice.cpp
    host/jsonservice/jsonservicedatabase.hpp    host/jsonservice/jsonservicedatabase.cpp
)

target_include_directories(Host-JsonService
    PUBLIC host
    PUBLIC api
    PUBLIC "${json_SOURCE_DIR}/include/"
    PUBLIC "${json-schema-validator_SOURCE_DIR}/src/"
)

# ............................................................................ #
# LoggerService

add_library(Host-LoggerService STATIC
    host/loggerservice/logger.hpp               host/loggerservice/logger.cpp
    host/loggerservice/loggerservice.hpp        host/loggerservice/loggerservice.cpp
)

target_include_directories(Host-LoggerService
    PUBLIC host
    PUBLIC api
)

target_link_libraries(Host-LoggerService
    spdlog
)

# ............................................................................ #
# main app

add_executable(Host
    ${apiHeaders}

    host/api/clientwrapper.hpp  host/api/clientwrapper.cpp
    host/api/hostapiwrapper.hpp host/api/hostapiwrapper.cpp
    host/api/versionservice.hpp host/api/versionservice.cpp

    host/cli/clihandler.hpp host/cli/clihandler.cpp
    host/cli/cliinput.hpp

    host/json/jsonservice.hpp            host/json/jsonservice.cpp
    host/json/schemaconstants.hpp        host/json/schemaconstants.cpp
    host/json/schemaconstantsbuilder.hpp host/json/schemaconstantsbuilder.cpp

    host/operationmodes/operationmode.hpp
    host/operationmodes/safecast.hpp       host/operationmodes/safecast.cpp

    host/operationmodes/help/entrypoint.hpp         host/operationmodes/help/entrypoint.cpp
    host/operationmodes/help/helpmodedefinition.hpp

    host/operationmodes/remote/entrypoint.hpp       host/operationmodes/remote/entrypoint.cpp
    host/operationmodes/remote/remoterundefinition.hpp

    host/operationmodes/schemaExport/entrypoint.hpp host/operationmodes/schemaExport/entrypoint.cpp
    host/operationmodes/schemaExport/schemaexportmodedefinition.hpp

    host/operationmodes/shared/defs/loggingdefinition.hpp
    host/operationmodes/shared/basemodedefinition.hpp

    host/operationmodes/simulation/entrypoint.hpp   host/operationmodes/simulation/entrypoint.cpp
    host/operationmodes/simulation/simulationmodedefinition.hpp
    host/operationmodes/simulation/defs/matchdefinition.hpp
    host/operationmodes/simulation/defs/simulatordefinition.hpp

    host/operationmodes/template/entrypoint.hpp     host/operationmodes/template/entrypoint.cpp
    host/operationmodes/template/templatemodedefinition.hpp

    host/constants.hpp host/constants.cpp
    host/errors.hpp
    host/main.cpp

    inputs/config/simulation.json
    inputs/config/template.json
)

target_include_directories(Host
    PRIVATE "${argparse_SOURCE_DIR}/include"
    PRIVATE "${json_SOURCE_DIR}/include/"
    PRIVATE "${json-schema-validator_SOURCE_DIR}/src/"
    PRIVATE host
    PRIVATE api
)

target_link_libraries(Host
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    Host-LoggerService
    Host-FileService
    Host-JsonService
)

# ---------------------------------------------------------------------------- #
# Engine Base

add_library(Engine-Base STATIC
    ${apiHeaders}

    engine-base/services.hpp engine-base/services.cpp

    engine-base/entrypoint.cpp
    engine-base/loggerservice.hpp engine-base/loggerservice.cpp
)

target_include_directories(Engine-Base
    PUBLIC api
)

set_target_properties(Engine-Base PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------- #
# Gen 1 Engine

add_library(Engine-Gen1 SHARED
    ${apiHeaders}

    engine-gen1/entrypoint.cpp
)

target_link_libraries(Engine-Gen1 PUBLIC
    Engine-Base
)

target_include_directories(Engine-Gen1
    PUBLIC "engine-base"
    PUBLIC api
)

# ============================================================================ #
# tests

include(GoogleTest)

enable_testing()

add_executable(Test
    test/main.cpp

    test/fileservice/fileservicetest.hpp test/fileservice/fileservicetest.cpp

    test/serviceadapters/fileservicedatabasetestadapter.hpp test/serviceadapters/fileservicedatabasetestadapter.cpp
    test/serviceadapters/jsonservicedatabaseadapter.hpp     test/serviceadapters/jsonservicedatabaseadapter.cpp
    test/serviceadapters/loggerserviceadapter.hpp           test/serviceadapters/loggerserviceadapter.cpp
)

target_include_directories(Test
    PRIVATE host
    PRIVATE test
    PRIVATE api
)

if (TARGET GTest::gtest_main)
    message("found it!")
else()
    message("no gtest!")
endif()

target_link_libraries(Test
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    Host-LoggerService
    Host-FileService
    Host-JsonService
)

gtest_discover_tests(Test)
