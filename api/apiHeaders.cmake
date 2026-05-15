add_library(Api-Headers INTERFACE)

target_include_directories(Api-Headers INTERFACE
    INTERFACE api
)

target_sources(Api-Headers INTERFACE
    api/ApiStatusCode.hpp
    api/CallingConventions.hpp
    api/ClientApi.hpp
    api/FeatureTags.hpp
    api/HostApi.hpp
    api/Version.hpp

    api/services/ICsvService.hpp
    api/services/IErrorService.hpp
    api/services/IFileService.hpp
    api/services/IJsonService.hpp
    api/services/ILoggerService.hpp
    api/services/IMemoryService.hpp
    api/services/IRngService.hpp
    api/services/IVersionService.hpp

    api/services/JsonService/IJsonService_Database.hpp
    api/services/JsonService/IJsonService_ItemAccess.hpp
    api/services/JsonService/IJsonService_SchemaBuilder.hpp
    api/services/JsonService/IJsonService_Types.hpp

    api/runmodes/IFileServiceDefinition.hpp
    api/runmodes/IMatchDefinition.hpp
    api/runmodes/ITemplatesDefinition.hpp
)
