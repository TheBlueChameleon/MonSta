#include <fstream>
#include <iostream>
#include <string>
using namespace std::string_literals;

#include "../errors.hpp"

#include "../logging/loggerservice.hpp"

#include "fileservicedatabase.hpp"
#include "fileserviceoperations.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    FileServiceDatabase FileServiceDatabase::instance;

    FileServiceDatabase::FileServiceDatabase() :
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
        auto it = oStreams.find(filename);
        if (it == oStreams.end())
        {
            const std::filesystem::path resolved = outputBasePath / filename;
            LoggerService::traceF("creating stream '{}'", resolved.c_str());
            auto [simpleStreamPtr, overwritten] = createStream(resolved, createDirectories, overwrite);

            if (dynamic_cast<std::ofstream*>(simpleStreamPtr))
            {
                addCreatedFile_internal(createdFileInfo, filename, overwritten);
            }

            auto synchronizedStreamPtr = new SynchronizedOStream(simpleStreamPtr);

            /* emplacement = pair<iterator, bool newlyCreatedItem> */
            /* iterator = pair<key*, value*> */
            auto emplacement = oStreams.emplace(filename, synchronizedStreamPtr);

            // TODO: throw if !newlyCreatedItem?

            return *emplacement.first->second;
        }
        else
        {
            return *it->second;
        }
    }

    const std::list<CreatedFileInfo>& FileServiceDatabase::getCreatedFileInfo() const
    {
        auto lock = std::lock_guard(mutex);
        return createdFileInfo;
    }

    static void addCreatedFile_internal(std::list<FileService::CreatedFileInfo>& createdFileInfo,
                                        const std::filesystem::__cxx11::path& filename,
                                        const bool overwritten
                                       )
    {
        createdFileInfo.emplace_back(filename, overwritten);
    }

    void FileServiceDatabase::addCreatedFile(const std::filesystem::__cxx11::path& filename, const bool overwritten)
    {
        auto lock = std::lock_guard(mutex);
        addCreatedFile_internal(createdFileInfo, filename, overwritten);
    }
}
