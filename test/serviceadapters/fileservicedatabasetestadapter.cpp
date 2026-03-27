#include "fileservicedatabasetestadapter.hpp"

using namespace FileService;

FileServiceDatabaseTestAdapter& FileServiceDatabaseTestAdapter::getInstance()
{
    return static_cast<FileServiceDatabaseTestAdapter&>(FileServiceDatabase::getInstance());
}

void FileServiceDatabaseTestAdapter::reset()
{
    overwrite         = false;
    createDirectories = false;
    dryMode           = false;

    inputBasePath  = std::filesystem::current_path();
    outputBasePath = std::filesystem::current_path();

    createdFileInfo.clear();
    oStreams.clear();
}
