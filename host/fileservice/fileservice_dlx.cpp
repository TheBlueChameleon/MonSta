#include <fstream>

#include "errorservice/errorservice.hpp"

#include "loggerservice/loggerservice.hpp"

#include "fileservice.hpp"
#include "fileservice_dlx.hpp"
#include "fileservicedatabase.hpp"
#include "fileserviceoperations.hpp"

namespace FileService
{
    const char* const HOST_API_CALL getInputBasePath_dlx()
    {
        return getInputBasePath().c_str();
    }

    const char* const HOST_API_CALL getOutputBasePath_dlx()
    {
        return getOutputBasePath().c_str();
    }

    void HOST_API_CALL setInputBasePath_dlx(const char* const newBase)
    {
        setInputBasePath(newBase);
    }

    void HOST_API_CALL setOutputBasePath_dlx(const char* const newBase)
    {
        setOutputBasePath(newBase);
    }

    IMemoryService::MemoryBlock HOST_API_CALL read_dlx(const char* const filename)
    {
        try
        {
            auto stream = getDatabase().getReadStream(filename);
            LoggerService::traceF("reading from {}", filename);
            const auto size = getFileSize(stream);

            IMemoryService::MemoryBlock result = MemoryService::allocate(size);
            stream.read(result.data, size);

            return result;
        }
        catch (const std::exception& e)
        {
            ErrorService::setError(ApiStatusCode::IO_ERROR, e.what());
            return IMemoryService::MemoryBlock {nullptr, 0};
        }
    }

    void HOST_API_CALL write_dlx(const char* const filename, const char* const content)
    {
        try
        {
            write(filename, content);
        }
        catch (const std::exception& e)
        {
            ErrorService::setError(ApiStatusCode::IO_ERROR, e.what());
        }
    }

    void HOST_API_CALL writeBinary_dlx(const char* const filename, const void* const data, size_t length)
    {
        try
        {
            writeBinary(
                filename,
                std::span(reinterpret_cast<const std::byte*>(data), length)
            );
        }
        catch (const std::exception& e)
        {
            ErrorService::setError(ApiStatusCode::IO_ERROR, e.what());
        }
    }

}
