#ifndef FILESERVICEDB_H
#define FILESERVICEDB_H

#include <filesystem>
#include <list>
#include <memory>
#include <semaphore>
#include <span>
#include <unordered_map>

#include "createdfileinfo.hpp"

namespace FileService
{
    class SynchronizedOStream;

    class FileServiceDatabase
    {
        private:
            static FileServiceDatabase instance;

            std::binary_semaphore smph;

            bool overwrite         = false;
            bool createDirectories = false;
            bool dryMode           = false;

            std::filesystem::path outputBasePath;
            std::list<FileService::CreatedFileInfo> createdFileInfo;

            std::unordered_map<std::filesystem::path, SynchronizedOStream> oStreams;

        protected:
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

            const std::filesystem::path& getOutputBasePath();
            void setOutputBasePath(const std::filesystem::path& newBase);

            SynchronizedOStream& getOrCreateStream(const std::filesystem::path& filename);

            const std::list<FileService::CreatedFileInfo>& getCreatedFileInfo();
            void addCreatedFile(const std::filesystem::path& filename, const bool overwritten);
    };
}

#endif // FILESERVICEDB_H
