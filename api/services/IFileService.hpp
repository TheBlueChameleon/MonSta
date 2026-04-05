#ifndef IFILESERVICE_H
#define IFILESERVICE_H

#include <stddef.h>

#include <CallingConventions.hpp>

#include <services/IMemoryService.hpp>

struct IFileService
{
    static constexpr auto STDOUTSTREAM = ":stdout:";
    static constexpr auto DEBUGSTREAM  = ":debug:";
    static constexpr auto NULLSTREAM   = ":null:";

    const char* const(HOST_API_CALL* const getInputBase)();
    const char* const(HOST_API_CALL* const getOutputBase)();

    IMemoryService::MemoryBlock(HOST_API_CALL* const read)(const char* const filename);

    void (HOST_API_CALL* const write)(const char* const filename, const char* const content);
    void (HOST_API_CALL* const writeBinary)(const char* const filename, const void* const data, size_t length);
};

#endif // IFILESERVICE_H
