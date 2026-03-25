#include <iostream>
#include <fstream>
#include <string>
using namespace std::string_literals;

#include "../errors.hpp"

#include "fileservicedb.hpp"
#include "ostreamfactory.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    FileServiceDatabase FileServiceDatabase::instance;

    FileServiceDatabase::FileServiceDatabase() :
        smph(1),
        outputBasePath(std::filesystem::current_path())
    {}

    FileServiceDatabaseAccess::FileServiceDatabaseAccess() :
        instance(FileServiceDatabase::instance)
    {
        FileServiceDatabase::instance.smph.acquire();
    }

    FileServiceDatabaseAccess::~FileServiceDatabaseAccess()
    {
        FileServiceDatabase::instance.smph.release();
    }

    bool FileServiceDatabaseAccess::getOverwrite()
    {
        return instance.overwrite;
    }

    void FileServiceDatabaseAccess::setOverwrite(bool newOverwrite)
    {
        instance.overwrite = newOverwrite;
    }

    bool FileServiceDatabaseAccess::getCreateDirectories()
    {
        return instance.createDirectories;
    }

    void FileServiceDatabaseAccess::setCreateDirectories(bool newCreateDirectories)
    {
        instance.createDirectories = newCreateDirectories;
    }

    bool FileServiceDatabaseAccess::getDryMode()
    {
        return instance.dryMode;
    }

    void FileServiceDatabaseAccess::setDryMode(bool newDryMode)
    {
        instance.dryMode = newDryMode;
    }

    const std::filesystem::__cxx11::path& FileServiceDatabaseAccess::getOutputBasePath()
    {
        return instance.outputBasePath;
    }

    void FileServiceDatabaseAccess::setOutputBasePath(const std::filesystem::__cxx11::path& newBase)
    {
        instance.outputBasePath = newBase;
    }

    SynchronizedOStream& FileServiceDatabaseAccess::getOrCreateStream(
        const std::filesystem::__cxx11::path& filename
    )
    {
        auto it = instance.oStreams.find(filename);
        if (it == instance.oStreams.end())
        {
            auto [streamPtr, overwritten] = createStream(filename);

            if (dynamic_cast<std::ofstream*>(streamPtr.get()))
            {
                addCreatedFile(filename, overwritten);
            }

            /* emplacement = pair<iterator, bool newlyCreatedItem> */
            /* iterator = pair<key*, value*> */
            auto emplacement = instance.oStreams.emplace(filename, streamPtr);

            // TODO: throw if !newlyCreatedItem?

            return emplacement.first->second;
        }
        else
        {
            return it->second;
        }
    }

    const std::list<FileService::CreatedFileInfo>& FileServiceDatabaseAccess::getCreatedFileInfo()
    {
        return instance.createdFileInfo;
    }

    void FileServiceDatabaseAccess::addCreatedFile(const std::filesystem::path& filename, const bool overwritten)
    {
        instance.createdFileInfo.emplace_back(filename, overwritten);
    }
}
