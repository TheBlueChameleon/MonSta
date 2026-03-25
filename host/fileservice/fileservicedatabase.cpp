#include <fstream>
#include <iostream>
#include <string>
using namespace std::string_literals;

#include "../errors.hpp"

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
            auto [streamPtr, overwritten] = createStream(filename, createDirectories, overwrite);

            if (dynamic_cast<std::ofstream*>(streamPtr.get()))
            {
                addCreatedFile(filename, overwritten);
            }

            /* emplacement = pair<iterator, bool newlyCreatedItem> */
            /* iterator = pair<key*, value*> */
            auto emplacement = oStreams.emplace(filename, streamPtr);

            // TODO: throw if !newlyCreatedItem?

            return emplacement.first->second;
        }
        else
        {
            return it->second;
        }
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
