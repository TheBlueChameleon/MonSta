#include <algorithm>
#include <cstring>
#include <fstream>

#include "../logging/loggerservice.hpp"

#include "fileservice.hpp"
#include "fileservicedatabase.hpp"
#include "fileserviceoperations.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
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

    std::filesystem::__cxx11::path getOutputBasePath()
    {
        return FileServiceDatabase::getInstance().getOutputBasePath();
    }

    const char* const getOutputBasePath_cstr()
    {
        return getOutputBasePath().c_str();
    }

    void setOutputBasePath(const std::filesystem::__cxx11::path& newBase)
    {
        if (makeDirectoriesOrLog(newBase, getCreateDirectories()))
        {
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
        stream << content;
    }

    void write_cstr(const char* const filename, const char* const content)
    {
        write(filename, content);
    }

    void writeBinary(const std::filesystem::__cxx11::path& filename, const std::span<const std::byte> data)
    {
        auto& stream = FileServiceDatabase::getInstance().getOrCreateStream(filename);
        stream.write(data.data(), data.size());
    }

    void writeBinary_cstr(const char* const filename, const void* const data, size_t length)
    {
        writeBinary(filename, std::span(reinterpret_cast<const std::byte*>(data), length));
    }

    std::string read(const std::filesystem::__cxx11::path& filename)
    {
        auto stream = FileServiceDatabase::getInstance().getReadStream(filename);
        const auto size = getFileSize(stream);

        std::string result(size, '\0');
        stream.read(&result[0], size);

        return result;
    }

    FileContents read_cstr(const char* const filename)
    {
        auto stream = FileServiceDatabase::getInstance().getReadStream(filename);
        const auto size = getFileSize(stream);

        FileContents result = {new char[size], size};
        stream.read(result.data, size);

        return result;
    }

    void freeFileContents(FileContents& fileContents)
    {
        delete fileContents.data;
        fileContents.data = nullptr;
        fileContents.size = 0;
    }

    const std::list<CreatedFileInfo> getCreatedFileInfo()
    {
        return FileServiceDatabase::getInstance().getCreatedFileInfo();
    }
}
