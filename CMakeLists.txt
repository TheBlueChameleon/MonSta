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
)

# ---------------------------------------------------------------------------- #
# Main App

add_executable(App
    api/HostApi.hpp
    api/ILogger.hpp
    api/Version.hpp

    host/main.cpp

    host/hostapiwrapper.hpp host/hostapiwrapper.cpp
    host/logger.hpp host/logger.cpp

    host/clientwrapper.hpp host/clientwrapper.cpp
)

target_link_libraries(App
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    spdlog
)

# ---------------------------------------------------------------------------- #
# Gen 1 Engine

add_library(Engine-Gen1 SHARED
    api/HostApi.hpp
    api/Version.hpp

    engine-gen1/entry.cpp
)

target_link_libraries(Engine-Gen1 PUBLIC
    spdlog
)

# ---------------------------------------------------------------------------- #
# Experimental

add_executable(Playground
    playground/main.cpp
)

target_link_libraries(Playground
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
)
