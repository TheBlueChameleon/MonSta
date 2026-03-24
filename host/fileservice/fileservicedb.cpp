#include <iostream>

#include "fileservicedb.hpp"

FileServiceDatabase FileServiceDatabase::instance;

FileServiceDatabase::FileServiceDatabase() :
    base(std::filesystem::current_path()),
    smph(1)
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

const std::filesystem::__cxx11::path& FileServiceDatabaseAccess::getBase()
{
    return instance.base;
}

void FileServiceDatabaseAccess::setBase(const std::filesystem::__cxx11::path& newBase)
{
    instance.base = newBase;
}

const std::list<FileService::CreatedFileInfo>& FileServiceDatabaseAccess::getCreatedFileInfo()
{
    return instance.createdFileInfo;
}

void FileServiceDatabaseAccess::addCreatedFile(const std::filesystem::path& filename, const bool overwritten)
{
    instance.createdFileInfo.emplace_back(filename, overwritten);
}
