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
        return FileServiceDatabase::getInstance().getOverwrite();
    }

    void setOverwrite(bool newOverwrite)
    {
        FileServiceDatabase::getInstance().setOverwrite(newOverwrite);
    }

    bool getCreateDirectories()
    {
        return FileServiceDatabase::getInstance().getCreateDirectories();
    }

    void setCreateDirectories(bool newCreateDirectories)
    {
        FileServiceDatabase::getInstance().setCreateDirectories(newCreateDirectories);
    }

    bool getDryMode()
    {
        return FileServiceDatabase::getInstance().getDryMode();
    }

    void setDryMode(bool newDryMode)
    {
        FileServiceDatabase::getInstance().setDryMode(newDryMode);
    }

    std::filesystem::__cxx11::path getInputBasePath()
    {
        return FileServiceDatabase::getInstance().getInputBasePath();
    }

    const char* const getInputBasePath_cstr()
    {
        return getInputBasePath().c_str();
    }

    std::filesystem::__cxx11::path getOutputBasePath()
    {
        return FileServiceDatabase::getInstance().getOutputBasePath();
    }

    const char* const getOutputBasePath_cstr()
    {
        return getOutputBasePath().c_str();
    }

    void setInputBasePath(const std::filesystem::__cxx11::path& newBase)
    {
        if (std::filesystem::exists(newBase))
        {
            LoggerService::traceF("input directory set to {}", newBase.c_str());
            FileServiceDatabase::getInstance().setInputBasePath(newBase);
        }
    }

    void setInputBasePath_cstr(const char* const newBase)
    {
        setInputBasePath(newBase);
    }

    void setOutputBasePath(const std::filesystem::__cxx11::path& newBase)
    {
        if (makeDirectoriesOrLog(newBase, getCreateDirectories()))
        {
            LoggerService::traceF("output directory set to {}", newBase.c_str());
            FileServiceDatabase::getInstance().setOutputBasePath(newBase);
        }
    }

    void setOutputBasePath_cstr(const char* const newBase)
    {
        setOutputBasePath(newBase);
    }

    void write(const std::filesystem::__cxx11::path& filename, const std::string& content)
    {
        auto& stream = FileServiceDatabase::getInstance().getOrCreateStream(filename);
        LoggerService::traceF("writing into {}", filename.c_str());
        stream << content;
    }

    void write_cstr(const char* const filename, const char* const content)
    {
        write(filename, content);
    }

    void writeBinary(const std::filesystem::__cxx11::path& filename, const std::span<const std::byte> data)
    {
        auto& stream = FileServiceDatabase::getInstance().getOrCreateStream(filename);
        LoggerService::traceF("writing into {}", filename.c_str());
        stream.write(data.data(), data.size());
    }

    void writeBinary_cstr(const char* const filename, const void* const data, size_t length)
    {
        writeBinary(filename, std::span(reinterpret_cast<const std::byte*>(data), length));
    }

    std::string read(const std::filesystem::__cxx11::path& filename)
    {
        auto stream = FileServiceDatabase::getInstance().getReadStream(filename);
        LoggerService::traceF("reading from {}", filename.c_str());
        const auto size = getFileSize(stream);

        std::string result(size, '\0');
        stream.read(&result[0], size);

        return result;
    }

    IMemoryService::MemoryBlock read_cstr(const char* const filename)
    {
        auto stream = FileServiceDatabase::getInstance().getReadStream(filename);
        LoggerService::traceF("reading from {}", filename);
        const auto size = getFileSize(stream);

        IMemoryService::MemoryBlock result = MemoryService::allocate(size);
        stream.read(result.data, size);

        return result;
    }

    const std::list<CreatedFileInfo> getCreatedFileInfo()
    {
        return FileServiceDatabase::getInstance().getCreatedFileInfo();
    }

    IFileService exportService()
    {
        return IFileService(
                   getInputBasePath_cstr,
                   getOutputBasePath_cstr,

                   read_cstr,

                   write_cstr,
                   writeBinary_cstr
               );
    }

}
