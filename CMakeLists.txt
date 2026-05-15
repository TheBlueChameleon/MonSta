cmake_minimum_required(VERSION 3.16)

# ============================================================================ #
# language definition

project(MonSta-All LANGUAGES
    CXX
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================ #
# components

include(dependencies/CMakeLists.txt)
include(api/apiHeaders.cmake)

add_subdirectory(host)
add_subdirectory(engines)
add_subdirectory(tests)
