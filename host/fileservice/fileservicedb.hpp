#ifndef FILESERVICEDB_H
#define FILESERVICEDB_H

#include <filesystem>
#include <list>
#include <memory>
#include <semaphore>
#include <span>

#include "createdfileinfo.hpp"

class FileServiceDatabase
{
    private:
        static FileServiceDatabase instance;

        bool overwrite         = false;
        bool createDirectories = false;
        bool dryMode           = false;

        std::filesystem::path base;
        std::list<FileService::CreatedFileInfo> createdFileInfo;
        std::binary_semaphore smph;

        FileServiceDatabase();

        friend class FileServiceDatabaseAccess;
};

class FileServiceDatabaseAccess
{
    private:
        FileServiceDatabase& instance;

    public:
        FileServiceDatabaseAccess();
        ~FileServiceDatabaseAccess();

        bool getOverwrite();
        void setOverwrite(bool newOverwrite);

        bool getCreateDirectories();
        void setCreateDirectories(bool newCreateDirectories);

        bool getDryMode();
        void setDryMode(bool newDryMode);

        const std::filesystem::path& getBase();
        void setBase(const std::filesystem::path& newBase);

        const std::list<FileService::CreatedFileInfo>& getCreatedFileInfo();
        void addCreatedFile(const std::filesystem::path& filename, const bool overwritten);
};

#endif // FILESERVICEDB_H
