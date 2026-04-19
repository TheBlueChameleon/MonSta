#include <fstream>
#include <string>
using namespace std::string_literals;

#include "errorservice/errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "fileservicedatabase.hpp"
#include "fileserviceoperations.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    FileServiceDatabase::FileServiceDatabase() :
        inputBasePath(std::filesystem::current_path()),
        outputBasePath(std::filesystem::current_path())
    {}

    static void addCreatedFile_internal(std::list<FileService::CreatedFileInfo>& createdFileInfo,
                                        const std::filesystem::__cxx11::path&
                                        filename, const bool overwritten);

    bool FileServiceDatabase::getOverwrite() const
    {
        auto lock = std::lock_guard(mutex);
        return overwrite;
    }

    void FileServiceDatabase::setOverwrite(bool newOverwrite)
    {
        auto lock = std::lock_guard(mutex);
        overwrite = newOverwrite;
    }

    bool FileServiceDatabase::getCreateDirectories() const
    {
        auto lock = std::lock_guard(mutex);
        return createDirectories;
    }

    void FileServiceDatabase::setCreateDirectories(bool newCreateDirectories)
    {
        auto lock = std::lock_guard(mutex);
        createDirectories = newCreateDirectories;
    }

    bool FileServiceDatabase::getDryMode() const
    {
        auto lock = std::lock_guard(mutex);
        return dryMode;
    }

    void FileServiceDatabase::setDryMode(bool newDryMode)
    {
        auto lock = std::lock_guard(mutex);
        dryMode = newDryMode;
    }

    const std::filesystem::__cxx11::path& FileServiceDatabase::getInputBasePath() const
    {
        auto lock = std::lock_guard(mutex);
        return inputBasePath;
    }

    void FileServiceDatabase::setInputBasePath(const std::filesystem::path& newInputBasePath)
    {
        auto lock = std::lock_guard(mutex);
        inputBasePath = newInputBasePath;
    }

    const std::filesystem::__cxx11::path& FileServiceDatabase::getOutputBasePath() const
    {
        auto lock = std::lock_guard(mutex);
        return outputBasePath;
    }

    void FileServiceDatabase::setOutputBasePath(const std::filesystem::__cxx11::path& newBase)
    {
        auto lock = std::lock_guard(mutex);
        outputBasePath = newBase;
    }

    SynchronizedOStream& FileServiceDatabase::getOrCreateWriteStream(const std::filesystem::__cxx11::path& filename)
    {
        auto lock = std::lock_guard(mutex);

        /* iterator = pair<key*, value*> */
        auto lookup = oStreams.find(filename);
        if (lookup == oStreams.end())
        {
            const std::filesystem::path resolved = outputBasePath / filename;
            auto [simpleStreamPtr, overwritten] = createStream(resolved, createDirectories, overwrite);

            if (dynamic_cast<std::ofstream*>(simpleStreamPtr.get()))
            {
                addCreatedFile(filename, overwritten);
            }

            auto [iterator, newlyCreated] = oStreams.emplace(
                                                filename,
                                                new SynchronizedOStream(std::move(simpleStreamPtr))
                                            );
            if (!newlyCreated)
            {
                throw IllegalHostStateException("Encountered a previously existing stream for '"s + filename.c_str() + "'");
            }

            return *iterator->second;
        }
        else
        {
            return *lookup->second;
        }
    }

    std::ifstream FileServiceDatabase::createReadStream(const std::filesystem::__cxx11::path& filename)
    {
        auto lock = std::lock_guard(mutex);

        const auto resolvedFilename = inputBasePath / filename;
        if (!std::filesystem::exists(resolvedFilename))
        {
            throw IOError(
                "Attempting to read file '"s +
                resolvedFilename.c_str() +
                "', but it not exist"
            );
        }

        return std::ifstream(
                   resolvedFilename,
                   std::ifstream::in | std::ifstream::binary
               );
    }

    const std::list<CreatedFileInfo>& FileServiceDatabase::getCreatedFileInfo() const
    {
        auto lock = std::lock_guard(mutex);
        return createdFileInfo;
    }

    void FileServiceDatabase::addCreatedFile(const std::filesystem::__cxx11::path& filename, const bool overwritten)
    {
        auto lock = std::lock_guard(mutex);
        createdFileInfo.emplace_back(filename, overwritten);
    }
}
