cmake_minimum_required(VERSION 4.1.1)

include(FetchContent)
include(CMakePrintHelpers)
include(GNUInstallDirs)

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

FetchContent_Declare(
  argparse
  GIT_REPOSITORY git@github.com:p-ranav/argparse.git
  GIT_TAG "v3.2"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
  SYSTEM
)
FetchContent_Declare(
  json
  GIT_REPOSITORY git@github.com:nlohmann/json.git
  GIT_TAG "v3.12.0"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
  SYSTEM
)
FetchContent_Declare(
  json-schema-validator
  GIT_REPOSITORY git@github.com:pboettch/json-schema-validator.git
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

# more `FetchContent_Declare`s (if any). They should all be declared
# before any calls to FetchContent_Make_available (see docs for why).

FetchContent_MakeAvailable(argparse)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(json-schema-validator)
FetchContent_MakeAvailable(spdlog)

set(JSON_BuildTests OFF CACHE INTERNAL "")

# ============================================================================ #
# source file definitions

include_directories(
    api
    "${json_SOURCE_DIR}/include/"
)

# ---------------------------------------------------------------------------- #
# Shared

set(apiHeaders
    api/ClientApi.hpp
    api/HostApi.hpp
    api/ILoggerService.hpp
    api/IJsonService.hpp
    api/IVersionService.hpp
    api/MatchDefinitions.hpp
    api/Version.hpp
)

# ---------------------------------------------------------------------------- #
# Main App

cmake_print_variables(json_SOURCE_DIR)

add_executable(App
    ${apiHeaders}

    host/api/clientwrapper.hpp host/api/clientwrapper.cpp
    host/api/hostapiwrapper.hpp host/api/hostapiwrapper.cpp
    host/api/loggerservice.hpp host/api/loggerservice.cpp
    host/api/versionservice.hpp host/api/versionservice.cpp

    host/cli/clihandler.hpp host/cli/clihandler.cpp
    host/cli/cliinput.hpp
    host/cli/logger.hpp host/cli/logger.cpp

    host/defs/environmentdefinition.hpp
    host/defs/loggingdefinition.hpp
    host/defs/simulationinputs.hpp

    host/json/jsonservice.hpp host/json/jsonservice.cpp

    host/constants.hpp host/constants.cpp
    host/errors.hpp
    host/main.cpp

    config/foo.json
)

target_include_directories(App
    PRIVATE "${argparse_SOURCE_DIR}/include"
    PRIVATE "${json-schema-validator_SOURCE_DIR}/src/"
)

target_link_libraries(App
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    spdlog
)

# ---------------------------------------------------------------------------- #
# Engine Base

add_library(Engine-Base STATIC
    ${apiHeaders}

    engine-base/services.hpp engine-base/services.cpp

    engine-base/entrypoint.cpp
    engine-base/loggerservice.hpp engine-base/loggerservice.cpp
)

target_compile_options(Engine-Base PRIVATE -fPIC)

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
    PRIVATE "engine-base"
)
