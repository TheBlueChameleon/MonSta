cmake_minimum_required(VERSION 3.16)

# ============================================================================ #
# language definition

project(MonSta-Host LANGUAGES
    CXX
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================ #
# source file definitions

# ............................................................................ #
# CsvService

add_library(Host-CsvService STATIC
    ../api/services/ICsvService.hpp

    csvservice/csvservice.hpp      csvservice/csvservice.cpp
    csvservice/csvservice_dlx.hpp  csvservice/csvservice_dlx.cpp
)

target_include_directories(Host-CsvService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${rapidcsv_SOURCE_DIR}/src
)

target_link_libraries(Host-CsvService
    PRIVATE csv_backbone
)

# ............................................................................ #
# ErrorService

add_library(Host-ErrorService STATIC
    ../api/services/IErrorService.hpp

    errorservice/catchmacros.hpp
    errorservice/errors.hpp             errorservice/errors.cpp
    errorservice/errorservice.hpp       errorservice/errorservice.cpp
    errorservice/errorservice_dlx.hpp   errorservice/errorservice_dlx.cpp
)

target_include_directories(Host-ErrorService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
)

# ............................................................................ #
# FileService

add_library(Host-FileService STATIC
    ../api/services/IFileService.hpp
    ../api/services/IMemoryService.hpp

    fileservice/debugstream.hpp
    fileservice/fileservice.hpp             fileservice/fileservice.cpp
    fileservice/fileservice_dlx.hpp         fileservice/fileservice_dlx.cpp
    fileservice/fileservicedatabase.hpp     fileservice/fileservicedatabase.cpp
    fileservice/fileserviceoperations.hpp   fileservice/fileserviceoperations.cpp
    fileservice/nullstream.hpp
    fileservice/stdoutstream.hpp            fileservice/stdoutstream.cpp
    fileservice/synchronizedostream.hpp     fileservice/synchronizedostream.cpp
    fileservice/types.hpp
)

target_include_directories(Host-FileService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
)

# ............................................................................ #
# JsonService

add_library(Host-JsonService STATIC
    ../api/services/IJsonService.hpp
    ../api/services/IMemoryService.hpp

    jsonservice/handleconverter.hpp                 jsonservice/handleconverter.cpp
    jsonservice/jsonschemabuilder.hpp               jsonservice/jsonschemabuilder.cpp
    jsonservice/jsonservice.hpp                     jsonservice/jsonservice.cpp
    jsonservice/jsonservice_database_dlx.hpp        jsonservice/jsonservice_database_dlx.cpp
    jsonservice/jsonservice_itemaccess_dlx.hpp      jsonservice/jsonservice_itemaccess_dlx.cpp
    jsonservice/jsonservice_schemabuilder_dlx.hpp   jsonservice/jsonservice_schemabuilder_dlx.cpp
    jsonservice/jsonservicedatabase.hpp             jsonservice/jsonservicedatabase.cpp
)

target_include_directories(Host-JsonService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${json_SOURCE_DIR}/include/
    PRIVATE ${json-schema-validator_SOURCE_DIR}/src/
)

target_link_libraries(Host-JsonService
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    Host-ErrorService
)

# ............................................................................ #
# LoggerService

add_library(Host-LoggerService STATIC
    ../api/services/ILoggerService.hpp

    loggerservice/logger.hpp                loggerservice/logger.cpp
    loggerservice/loggerservice.hpp         loggerservice/loggerservice.cpp
    loggerservice/loggerservice_dlx.hpp     loggerservice/loggerservice_dlx.cpp
)

target_include_directories(Host-LoggerService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
)

target_link_libraries(Host-LoggerService
    spdlog
)

# ............................................................................ #
# MemoryService

add_library(Host-MemoryService STATIC
    ../api/services/IMemoryService.hpp

    memoryservice/memoryservice.hpp         memoryservice/memoryservice.cpp
    memoryservice/memoryservice_dlx.hpp     memoryservice/memoryservice_dlx.cpp
)

target_include_directories(Host-MemoryService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
)

# ............................................................................ #
# RngService

add_library(Host-RngService STATIC
    ../api/services/IRngService.hpp

    rngservice/rngservice.hpp       rngservice/rngservice.cpp
    rngservice/rngservice_dlx.hpp   rngservice/rngservice_dlx.cpp
)

target_include_directories(Host-RngService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${pcg-cpp_SOURCE_DIR}/include
)

# ............................................................................ #
# VersionService

add_library(Host-VersionService STATIC
    ../api/services/IMemoryService.hpp
    ../api/services/IVersionService.hpp

    versionservice/versionservice.hpp       versionservice/versionservice.cpp
    versionservice/versionservice_dlx.hpp   versionservice/versionservice_dlx.cpp
)

target_include_directories(Host-VersionService
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
)

# ............................................................................ #
# main app

add_executable(Host
    api/clientwrapper.hpp                                          api/clientwrapper.cpp
    api/hostapiprovider.hpp                                        api/hostapiprovider.cpp

    cli/clihandler.hpp                                             cli/clihandler.cpp
    cli/cliinput.hpp

    operationmodes/entrypoint.hpp                                  operationmodes/entrypoint.cpp
    operationmodes/operationmode.hpp                               operationmodes/operationmode.cpp

    operationmodes/help/helpmodedefinition.hpp
    operationmodes/help/helpmodeimplementation.hpp                 operationmodes/help/helpmodeimplementation.cpp

    operationmodes/remote/remoterundefinition.hpp

    operationmodes/schemaExport/schemaexportmodedefinition.hpp
    operationmodes/schemaExport/schemaexportmodeimplementation.hpp operationmodes/schemaExport/schemaexportmodeimplementation.cpp

    operationmodes/shared/basemodedefinition.hpp
    operationmodes/shared/schemavalidationconstants.hpp            operationmodes/shared/schemavalidationconstants.cpp
    operationmodes/shared/utils.hpp                                operationmodes/shared/utils.cpp

    operationmodes/shared/defs/loggingdefinition.hpp
    operationmodes/shared/defs/pathsdefinition.hpp

    operationmodes/remote/remotemodeimplemetnation.hpp             operationmodes/remote/remotemodeimplemetnation.cpp

    operationmodes/simulation/simulationmodedefinition.hpp
    operationmodes/simulation/simulationmodeimplementation.hpp     operationmodes/simulation/simulationmodeimplementation.cpp
    operationmodes/simulation/defs/matchdefinition.hpp
    operationmodes/simulation/defs/simulatordefinition.hpp

    operationmodes/template/templatemodedefinition.hpp
    operationmodes/template/templatemodeimplementation.hpp         operationmodes/template/templatemodeimplementation.cpp
    operationmodes/template/defs/templatesdefinition.hpp

    constants.hpp       constants.cpp
    main.cpp
)

target_include_directories(Host
    PRIVATE ${CMAKE_SOURCE_DIR}/host
    PRIVATE ${CMAKE_SOURCE_DIR}/api
    PRIVATE ${argparse_SOURCE_DIR}/include
    PRIVATE ${json_SOURCE_DIR}/include/
    PRIVATE ${json-schema-validator_SOURCE_DIR}/src/
)

target_link_libraries(Host
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
