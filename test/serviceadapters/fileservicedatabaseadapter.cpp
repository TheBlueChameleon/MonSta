#include "fileservicedatabaseadapter.hpp"

using namespace FileService;

FileServiceDatabaseAdapter& FileServiceDatabaseAdapter::getInstance()
{
    return static_cast<FileServiceDatabaseAdapter&>(FileServiceDatabase::getInstance());
}

void FileServiceDatabaseAdapter::reset()
{
    overwrite         = false;
    createDirectories = false;
    dryMode           = false;

    inputBasePath  = std::filesystem::current_path();
    outputBasePath = std::filesystem::current_path();

    createdFileInfo.clear();
    oStreams.clear();
}
