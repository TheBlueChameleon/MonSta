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

add_subdirectory(libcsv)

# ============================================================================ #
# source file definitions

# ---------------------------------------------------------------------------- #
# Shared

set(apiHeaders
    api/CallingConventions.hpp
    api/ClientApi.hpp
    api/ApiStatusCode.hpp
    api/FeatureTags.hpp
    api/HostApi.hpp
    api/Version.hpp

    api/services/ICsvService.hpp
    api/services/IErrorService.hpp
    api/services/IFileService.hpp
    api/services/IJsonService.hpp
    api/services/ILoggerService.hpp
    api/services/IMemoryService.hpp
    api/services/IVersionService.hpp

    api/services/JsonService/IJsonService_Database.hpp
    api/services/JsonService/IJsonService_ItemAccess.hpp
    api/services/JsonService/IJsonService_SchemaBuilder.hpp
    api/services/JsonService/IJsonService_Types.hpp

    api/runmodes/IFileServiceDefinition.hpp
    api/runmodes/IMatchDefinition.hpp
    api/runmodes/ITemplatesDefinition.hpp
)

# ---------------------------------------------------------------------------- #
# Main App

# ............................................................................ #
# CsvService

add_library(Host-CsvService STATIC
    host/csvservice/csvservice.hpp      host/csvservice/csvservice.cpp
    host/csvservice/csvservice_dlx.hpp  host/csvservice/csvservice_dlx.cpp
)

target_include_directories(Host-CsvService
    PUBLIC host
    PUBLIC api
    PUBLIC ${rapidcsv_SOURCE_DIR}/src
)

target_link_libraries(Host-CsvService
    PRIVATE csv_backbone
)

# ............................................................................ #
# ErrorService

add_library(Host-ErrorService STATIC
    host/errorservice/catchmacros.hpp
    host/errorservice/errors.hpp            host/errorservice/errors.cpp
    host/errorservice/errorservice.hpp      host/errorservice/errorservice.cpp
    host/errorservice/errorservice_dlx.hpp  host/errorservice/errorservice_dlx.cpp
)

target_include_directories(Host-ErrorService
    PUBLIC host
    PUBLIC api
)

# ............................................................................ #
# FileService

add_library(Host-FileService STATIC
    host/fileservice/debugstream.hpp
    host/fileservice/fileservice.hpp            host/fileservice/fileservice.cpp
    host/fileservice/fileservice_dlx.hpp        host/fileservice/fileservice_dlx.cpp
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
    host/jsonservice/handleconverter.hpp                host/jsonservice/handleconverter.cpp
    host/jsonservice/jsonservice.hpp                    host/jsonservice/jsonservice.cpp
    host/jsonservice/jsonservice_database_dlx.hpp       host/jsonservice/jsonservice_database_dlx.cpp
    host/jsonservice/jsonservice_itemaccess_dlx.hpp     host/jsonservice/jsonservice_itemaccess_dlx.cpp
    host/jsonservice/jsonservice_schemabuilder_dlx.hpp  host/jsonservice/jsonservice_schemabuilder_dlx.cpp
    host/jsonservice/jsonservicedatabase.hpp            host/jsonservice/jsonservicedatabase.cpp
    host/jsonservice/jsonschemabuilder.hpp              host/jsonservice/jsonschemabuilder.cpp
)

target_include_directories(Host-JsonService
    PUBLIC host
    PUBLIC api
    PUBLIC ${json_SOURCE_DIR}/include/
    PUBLIC ${json-schema-validator_SOURCE_DIR}/src/
)

target_link_libraries(Host-JsonService
    nlohmann_json_schema_validator
    Host-ErrorService
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
# MemoryService

add_library(Host-MemoryService STATIC
    host/memoryservice/memoryservice.hpp        host/memoryservice/memoryservice.cpp
    host/memoryservice/memoryservice_dlx.hpp    host/memoryservice/memoryservice_dlx.cpp
)

target_include_directories(Host-MemoryService
    PUBLIC host
    PUBLIC api
)

# ............................................................................ #
# VersionService

add_library(Host-VersionService STATIC
    host/versionservice/versionservice.hpp     host/versionservice/versionservice.cpp
    host/versionservice/versionservice_dlx.hpp host/versionservice/versionservice_dlx.cpp
)

target_include_directories(Host-VersionService
    PUBLIC host
    PUBLIC api
)

# ............................................................................ #
# main app

add_executable(Host
    ${apiHeaders}

    host/api/clientwrapper.hpp                                          host/api/clientwrapper.cpp
    host/api/hostapiprovider.hpp                                        host/api/hostapiprovider.cpp

    host/cli/clihandler.hpp                                             host/cli/clihandler.cpp
    host/cli/cliinput.hpp

    host/operationmodes/entrypoint.hpp                                  host/operationmodes/entrypoint.cpp
    host/operationmodes/operationmode.hpp                               host/operationmodes/operationmode.cpp

    host/operationmodes/help/helpmodeimplementation.hpp                 host/operationmodes/help/helpmodeimplementation.cpp
    host/operationmodes/help/helpmodedefinition.hpp

    host/operationmodes/remote/remoterundefinition.hpp

    host/operationmodes/schemaExport/schemaexportmodeimplementation.hpp host/operationmodes/schemaExport/schemaexportmodeimplementation.cpp
    host/operationmodes/schemaExport/schemaexportmodedefinition.hpp

    host/operationmodes/shared/basemodedefinition.hpp
    host/operationmodes/shared/schemavalidationconstants.hpp            host/operationmodes/shared/schemavalidationconstants.cpp
    host/operationmodes/shared/utils.hpp                                host/operationmodes/shared/utils.cpp

    host/operationmodes/shared/defs/loggingdefinition.hpp
    host/operationmodes/shared/defs/pathsdefinition.hpp

    host/operationmodes/remote/remotemodeimplemetnation.hpp             host/operationmodes/remote/remotemodeimplemetnation.cpp

    host/operationmodes/simulation/simulationmodeimplementation.hpp     host/operationmodes/simulation/simulationmodeimplementation.cpp
    host/operationmodes/simulation/simulationmodedefinition.hpp
    host/operationmodes/simulation/defs/matchdefinition.hpp
    host/operationmodes/simulation/defs/simulatordefinition.hpp

    host/operationmodes/template/templatemodeimplementation.hpp         host/operationmodes/template/templatemodeimplementation.cpp
    host/operationmodes/template/templatemodedefinition.hpp
    host/operationmodes/template/defs/templatesdefinition.hpp

    host/constants.hpp host/constants.cpp
    host/main.cpp

    inputs/config/simulation.json
    inputs/config/templates.json
)

target_include_directories(Host
    PRIVATE ${argparse_SOURCE_DIR}/include
    PRIVATE ${json_SOURCE_DIR}/include/
    PRIVATE ${json-schema-validator_SOURCE_DIR}/src/
    PRIVATE host
    PRIVATE api
)

target_link_libraries(Host
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-VersionService
)

# ---------------------------------------------------------------------------- #
# Engine Base

add_library(Engine-Base STATIC
    ${apiHeaders}

    engine-base/base/clientapi.cpp

    engine-base/base/errors.hpp                                     engine-base/base/errors.cpp
    engine-base/base/errorbuffer.hpp                                engine-base/base/errorbuffer.cpp
    engine-base/base/enginebase.hpp                                 engine-base/base/enginebase.cpp
    engine-base/base/globals.hpp                                    engine-base/base/globals.cpp

    engine-base/services/services.hpp                               engine-base/services/services.cpp
    engine-base/services/csvservice.hpp                             engine-base/services/csvservice.cpp
    engine-base/services/errorservice.hpp                           engine-base/services/errorservice.cpp
    engine-base/services/fileservice.hpp                            engine-base/services/fileservice.cpp
    engine-base/services/jsonservice.hpp
    engine-base/services/jsonservice/jsonwrapper.hpp                engine-base/services/jsonservice/jsonwrapper.cpp
    engine-base/services/jsonservice/jsonservice_database.hpp       engine-base/services/jsonservice/jsonservice_database.cpp
    engine-base/services/jsonservice/jsonservice_itemaccess.hpp     engine-base/services/jsonservice/jsonservice_itemaccess.cpp
    engine-base/services/jsonservice/jsonservice_schemabuilder.hpp  engine-base/services/jsonservice/jsonservice_schemabuilder.cpp
    engine-base/services/jsonservice/schemabuilder_wrapper.hpp      engine-base/services/jsonservice/schemabuilder_wrapper.cpp
    engine-base/services/loggerservice.hpp                          engine-base/services/loggerservice.cpp
    engine-base/services/memoryservice.hpp                          engine-base/services/memoryservice.cpp
)

target_include_directories(Engine-Base
    PUBLIC api
    PUBLIC engine-base
)

set_target_properties(Engine-Base PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------- #
# Gen 1 Engine

add_library(Engine-Gen1 SHARED
    ${apiHeaders}

    engine-gen1/clientapi.cpp

    engine-gen1/shared/schemavalidationconstants.hpp                engine-gen1/shared/schemavalidationconstants.cpp

    engine-gen1/shared/defs/mechanicsdefinition.hpp
    engine-gen1/shared/defs/pokemondatabaseentry.hpp        engine-gen1/shared/defs/pokemondatabaseentry.cpp
    engine-gen1/shared/defs/pokemondefition.hpp
    engine-gen1/shared/defs/pokemonstatus.hpp               engine-gen1/shared/defs/pokemonstatus.cpp
    engine-gen1/shared/defs/teamdefinition.hpp
    engine-gen1/shared/defs/typeinfo.hpp                    engine-gen1/shared/defs/typeinfo.cpp

    engine-gen1/shared/registry/pokemondatabase.hpp                 engine-gen1/shared/registry/pokemondatabase.cpp
    engine-gen1/shared/registry/registry.hpp                        engine-gen1/shared/registry/registry.cpp
    engine-gen1/shared/registry/typechart.hpp                       engine-gen1/shared/registry/typechart.cpp

    engine-gen1/shared/registry/effects/abstracteffecthandler.hpp
    engine-gen1/shared/registry/effects/effecthandlerdescriptor.hpp

    engine-gen1/shared/registry/moves/move.hpp                      engine-gen1/shared/registry/moves/move.cpp
    engine-gen1/shared/registry/moves/secondaryeffect.hpp

    engine-gen1/simulationmode/arena/pokemoninstance.hpp            engine-gen1/simulationmode/arena/pokemoninstance.cpp
    engine-gen1/simulationmode/arena/scene.hpp

    engine-gen1/simulationmode/setup/mechanicsdefinitionsetup.hpp   engine-gen1/simulationmode/setup/mechanicsdefinitionsetup.cpp
    engine-gen1/simulationmode/setup/pokemondefinitionsetup.hpp     engine-gen1/simulationmode/setup/pokemondefinitionsetup.cpp
    engine-gen1/simulationmode/setup/setuperrorhandling.hpp         engine-gen1/simulationmode/setup/setuperrorhandling.cpp
    engine-gen1/simulationmode/setup/teamdefinitionsetup.hpp        engine-gen1/simulationmode/setup/teamdefinitionsetup.cpp
    engine-gen1/simulationmode/setup/typedefinitionsetup.hpp        engine-gen1/simulationmode/setup/typedefinitionsetup.cpp

    engine-gen1/simulationmode/simulationmode.hpp                   engine-gen1/simulationmode/simulationmode.cpp

    engine-gen1/templatesmode/templatesmode.hpp                     engine-gen1/templatesmode/templatesmode.cpp
)

target_link_libraries(Engine-Gen1 PUBLIC
    Engine-Base
)

target_include_directories(Engine-Gen1
    PUBLIC engine-gen1
    PUBLIC engine-base
    PUBLIC api
)

# ============================================================================ #
# tests

include(GoogleTest)

enable_testing()

add_executable(Test
    test/main.cpp

    test/csvservice/csvservicetest.hpp                      test/csvservice/csvservicetest.cpp

    test/fileservice/fileservicetest.hpp                    test/fileservice/fileservicetest.cpp
    test/fileservice/fileservicedatabasetest.hpp            test/fileservice/fileservicedatabasetest.cpp

    test/jsonservice/jsonservicedatabasetest.hpp            test/jsonservice/jsonservicedatabasetest.cpp
    test/jsonservice/jsonschemabuildertest.hpp              test/jsonservice/jsonschemabuildertest.cpp

    test/versionservice/versionservicetest.hpp              test/versionservice/versionservicetest.cpp

    test/serviceadapters/loggerserviceadapter.hpp           test/serviceadapters/loggerserviceadapter.cpp
)

target_include_directories(Test
    PRIVATE host
    PRIVATE test
    PRIVATE api
)

if (TARGET GTest::gtest_main)
    message("found gtest!")
else()
    message("no gtest!")
endif()

target_link_libraries(Test
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    Host-CsvService
    Host-ErrorService
    Host-FileService
    Host-JsonService
    Host-LoggerService
    Host-MemoryService
    Host-VersionService
)

gtest_discover_tests(Test)
