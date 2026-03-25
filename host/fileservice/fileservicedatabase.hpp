#ifndef FILESERVICEDATABASE_H
#define FILESERVICEDATABASE_H

#include <filesystem>
#include <list>
#include <memory>
#include <mutex>
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

            std::mutex mutable mutex;

            bool overwrite         = false;
            bool createDirectories = false;
            bool dryMode           = false;

            std::filesystem::path outputBasePath;
            std::list<FileService::CreatedFileInfo> createdFileInfo;

            std::unordered_map<std::filesystem::path, SynchronizedOStream> oStreams;

        protected:
            FileServiceDatabase();

        public:
            static FileServiceDatabase& getInstance();

            bool getOverwrite() const;
            void setOverwrite(bool newOverwrite);

            bool getCreateDirectories() const;
            void setCreateDirectories(bool newCreateDirectories);

            bool getDryMode() const;
            void setDryMode(bool newDryMode);

            const std::filesystem::path& getOutputBasePath() const;
            void setOutputBasePath(const std::filesystem::path& newBase);

            SynchronizedOStream& getOrCreateStream(const std::filesystem::path& filename);

            const std::list<FileService::CreatedFileInfo>& getCreatedFileInfo() const;
            void addCreatedFile(const std::filesystem::path& filename, const bool overwritten);

            friend class FileServiceDatabaseAccess;
    };
}

#endif // FILESERVICEDATABASE_H
