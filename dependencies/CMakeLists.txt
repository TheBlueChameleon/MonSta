include(FetchContent)

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
  GIT_TAG ${nlohmann_json_VERSION}
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
  pcg-cpp
  GIT_REPOSITORY https://github.com/imneme/pcg-cpp
  GIT_TAG "v0.98.1"
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
FetchContent_MakeAvailable(pcg-cpp)
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(googletest)

add_subdirectory(dependencies/libcsv)

# include(dependencies/libcsv.cmake)
