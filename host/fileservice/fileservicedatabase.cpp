#include <fstream>
#include <iostream>
#include <string>
using namespace std::string_literals;

#include "errors.hpp"

#include "logging/loggerservice.hpp"

#include "fileservicedatabase.hpp"
#include "fileserviceoperations.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    FileServiceDatabase FileServiceDatabase::instance;

    FileServiceDatabase::FileServiceDatabase() :
        inputBasePath(std::filesystem::current_path()),
        outputBasePath(std::filesystem::current_path())
    {}

    FileServiceDatabase& FileServiceDatabase::getInstance()
    {
        return instance;
    }

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

    SynchronizedOStream& FileServiceDatabase::getOrCreateStream(const std::filesystem::__cxx11::path& filename)
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

            auto [iterator, newlyCreated] = oStreams.emplace(filename, new SynchronizedOStream(simpleStreamPtr));
            if (!newlyCreated)
            {
                throw IllegalStateException("Encountered a previously existing stream for '"s + filename.c_str() + "'");
            }

            return *iterator->second;
        }
        else
        {
            return *lookup->second;
        }
    }

    std::ifstream FileServiceDatabase::getReadStream(const std::filesystem::__cxx11::path& filename)
    {
        auto lock = std::lock_guard(mutex);
        const auto target = inputBasePath / filename;

        if (!std::filesystem::exists(target))
        {
            LoggerService::errorF("File to read '{}' does not exist", target.c_str());
            return std::ifstream();
        }

        return std::ifstream(
                   target,
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
