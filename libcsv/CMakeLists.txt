cmake_minimum_required(VERSION 3.16)

include(FetchContent)

# ============================================================================ #
# language definition

project(libcsv
    LANGUAGES C
)

# ============================================================================ #
# external dependencies

FetchContent_Declare(
  libcsv
  GIT_REPOSITORY https://github.com/rgamble/libcsv
  GIT_TAG "b1d5212831842ee5869d99bc208a21837e4037d5"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
  SYSTEM
)
FetchContent_MakeAvailable(libcsv)

add_library(csv_backbone STATIC
    ${libcsv_SOURCE_DIR}/csv.h
    ${libcsv_SOURCE_DIR}/libcsv.c
)

target_include_directories(csv_backbone PUBLIC
    ${libcsv_SOURCE_DIR}
)

# ============================================================================ #
# source file definitions, maybe?
