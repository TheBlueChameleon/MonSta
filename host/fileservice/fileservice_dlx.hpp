#ifndef FILESERVICE_DLX_HPP
#define FILESERVICE_DLX_HPP

#include <CallingConventions.hpp>

#include "memoryservice/memoryservice.hpp"

namespace FileService
{
    const char* const HOST_API_CALL getInputBasePath_dlx();
    const char* const HOST_API_CALL getOutputBasePath_dlx();

    void HOST_API_CALL setInputBasePath_dlx(const char* const newBase);
    void HOST_API_CALL setOutputBasePath_dlx(const char* const newBase);

    void HOST_API_CALL write_dlx(const char* const filename, const char* const content);
    void HOST_API_CALL writeBinary_dlx(const char* const filename, const void* const data, size_t length);

    IMemoryService::MemoryBlock HOST_API_CALL read_dlx(const char* const filename);
}

#endif // FILESERVICE_DLX_HPP
