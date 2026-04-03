#include <algorithm>
#include <cstring>
#include <fstream>

#include "loggerservice/loggerservice.hpp"

#include "fileservice.hpp"
#include "fileservicedatabase.hpp"
#include "fileserviceoperations.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    static FileServiceDatabase database;

    static const std::set<std::string> specialNames = {STDOUTSTREAM, DEBUGSTREAM, NULLSTREAM};

    bool isSpecialPath(const std::filesystem::path& path)
    {
        for (const auto& element : path)
        {
            if (specialNames.contains(element.c_str()))
            {
                return true;
            }
        }

        return false;
    }

    bool getOverwrite()
    {
        return database.getOverwrite();
    }

    void setOverwrite(bool newOverwrite)
    {
        database.setOverwrite(newOverwrite);
    }

    bool getCreateDirectories()
    {
        return database.getCreateDirectories();
    }

    void setCreateDirectories(bool newCreateDirectories)
    {
        database.setCreateDirectories(newCreateDirectories);
    }

    bool getDryMode()
    {
        return database.getDryMode();
    }

    void setDryMode(bool newDryMode)
    {
        database.setDryMode(newDryMode);
    }

    std::filesystem::__cxx11::path getInputBasePath()
    {
        return database.getInputBasePath();
    }

    const char* const getInputBasePath_dlx()
    {
        return getInputBasePath().c_str();
    }

    std::filesystem::__cxx11::path getOutputBasePath()
    {
        return database.getOutputBasePath();
    }

    const char* const getOutputBasePath_dlx()
    {
        return getOutputBasePath().c_str();
    }

    void setInputBasePath(const std::filesystem::__cxx11::path& newBase)
    {
        if (std::filesystem::exists(newBase))
        {
            LoggerService::traceF("input directory set to {}", newBase.c_str());
            database.setInputBasePath(newBase);
        }
    }

    void setInputBasePath_dlx(const char* const newBase)
    {
        setInputBasePath(newBase);
    }

    void setOutputBasePath(const std::filesystem::__cxx11::path& newBase)
    {
        if (makeDirectoriesOrLog(newBase, getCreateDirectories()))
        {
            LoggerService::traceF("output directory set to {}", newBase.c_str());
            database.setOutputBasePath(newBase);
        }
    }

    void setOutputBasePath_dlx(const char* const newBase)
    {
        setOutputBasePath(newBase);
    }

    void write(const std::filesystem::__cxx11::path& filename, const std::string_view content)
    {
        auto& stream = database.getOrCreateStream(filename);
        LoggerService::traceF("writing into {}", filename.c_str());
        stream << content;
    }

    void write_dlx(const char* const filename, const char* const content)
    {
        write(filename, content);
    }

    void writeBinary(const std::filesystem::__cxx11::path& filename, const std::span<const std::byte> data)
    {
        auto& stream = database.getOrCreateStream(filename);
        LoggerService::traceF("writing into {}", filename.c_str());
        stream.write(data.data(), data.size());
    }

    void writeBinary_dlx(const char* const filename, const void* const data, size_t length)
    {
        writeBinary(filename, std::span(reinterpret_cast<const std::byte*>(data), length));
    }

    std::string read(const std::filesystem::__cxx11::path& filename)
    {
        auto stream = database.getReadStream(filename);
        LoggerService::traceF("reading from {}", filename.c_str());
        const auto size = getFileSize(stream);

        std::string result(size, '\0');
        stream.read(&result[0], size);

        return result;
    }

    IMemoryService::MemoryBlock read_dlx(const char* const filename)
    {
        auto stream = database.getReadStream(filename);
        LoggerService::traceF("reading from {}", filename);
        const auto size = getFileSize(stream);

        IMemoryService::MemoryBlock result = MemoryService::allocate(size);
        stream.read(result.data, size);

        return result;
    }

    const std::list<CreatedFileInfo>& getCreatedFileInfo()
    {
        return database.getCreatedFileInfo();
    }

    IFileService exportService()
    {
        return IFileService(
                   getInputBasePath_dlx,
                   getOutputBasePath_dlx,

                   read_dlx,

                   write_dlx,
                   writeBinary_dlx
               );
    }

    FileServiceDatabase& getDatabase()
    {
        return database;
    }

}
