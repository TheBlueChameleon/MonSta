#include <iostream>

#include "filewriterconfig.hpp"

FileWriterConfig FileWriterConfig::instance;

FileWriterConfig::FileWriterConfig() :
    base(std::filesystem::current_path()),
    smph(1)
{}

FileWriterConfigAccess::FileWriterConfigAccess() :
    instance(FileWriterConfig::instance)
{
    FileWriterConfig::instance.smph.acquire();
}

FileWriterConfigAccess::~FileWriterConfigAccess()
{
    FileWriterConfig::instance.smph.release();
}

bool FileWriterConfigAccess::getOverwrite()
{
    return instance.overwrite;
}

void FileWriterConfigAccess::setOverwrite(bool newOverwrite)
{
    instance.overwrite = newOverwrite;
}

bool FileWriterConfigAccess::getCreateDirectories()
{
    return instance.createDirectories;
}

void FileWriterConfigAccess::setCreateDirectories(bool newCreateDirectories)
{
    instance.createDirectories = newCreateDirectories;
}

bool FileWriterConfigAccess::getDryMode()
{
    return instance.dryMode;
}

void FileWriterConfigAccess::setDryMode(bool newDryMode)
{
    instance.dryMode = newDryMode;
}

const std::filesystem::__cxx11::path& FileWriterConfigAccess::getBase()
{
    return instance.base;
}

void FileWriterConfigAccess::setBase(const std::filesystem::__cxx11::path& newBase)
{
    instance.base = newBase;
}

const std::list<FileWriterService::CreatedFileInfo>& FileWriterConfigAccess::getCreatedFileInfo()
{
    return instance.createdFileInfo;
}

void FileWriterConfigAccess::addCreatedFile(const std::filesystem::path& filename, const bool overwritten)
{
    instance.createdFileInfo.emplace_back(filename, overwritten);
}
