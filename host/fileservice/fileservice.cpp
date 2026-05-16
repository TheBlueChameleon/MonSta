#include <fstream>
#include <set>

#include "errorservice/errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "fileservice.hpp"
#include "fileservice_dlx.hpp"
#include "fileservicedatabase.hpp"
#include "fileserviceoperations.hpp"
#include "synchronizedostream.hpp"

using namespace std::string_literals;

namespace FileService
{
    static FileServiceDatabase database;

    static const std::set<std::string> specialNames =
    {
        IFileService::STDOUTSTREAM,
        IFileService::DEBUGSTREAM,
        IFileService::NULLSTREAM
    };

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

    std::filesystem::path getInputBasePath()
    {
        return database.getInputBasePath();
    }

    std::filesystem::path getOutputBasePath()
    {
        return database.getOutputBasePath();
    }

    void setInputBasePath(const std::filesystem::path& newBase)
    {
        if (std::filesystem::exists(newBase))
        {
            LoggerService::traceF("input directory set to {}", newBase.c_str());
            database.setInputBasePath(newBase);
        }
        else
        {
            throw IOError(
                "Invalid input directory: "s  + newBase.c_str()
            );
        }
    }

    void setOutputBasePath(const std::filesystem::path& newBase)
    {
        if (makeDirectoriesOrLog(newBase, getCreateDirectories()))
        {
            database.setOutputBasePath(newBase);
            LoggerService::traceF("output directory set to {}", newBase.c_str());
        }
        else
        {
            throw IOError(
                "Invalid output directory: "s  + newBase.c_str()
            );
        }
    }

    std::ifstream getInputStream(const std::filesystem::path& filename)
    {
        return database.createReadStream(filename);
    }

    std::string read(const std::filesystem::path& filename)
    {
        auto stream = database.createReadStream(filename);
        LoggerService::traceF("reading from {}", filename.c_str());
        const auto size = getFileSize(stream);

        std::string result(size, '\0');
        stream.read(&result[0], size);

        return result;
    }

    void write(const std::filesystem::path& filename, const std::string_view content)
    {
        auto& stream = database.getOrCreateWriteStream(filename);
        LoggerService::traceF("writing into {}", filename.c_str());
        stream << content;
    }

    void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data)
    {
        auto& stream = database.getOrCreateWriteStream(filename);
        LoggerService::traceF("writing into {}", filename.c_str());
        stream.write(data.data(), data.size());
    }

    const std::list<CreatedFileInfo>& getCreatedFileInfo()
    {
        return database.getCreatedFileInfo();
    }

}
