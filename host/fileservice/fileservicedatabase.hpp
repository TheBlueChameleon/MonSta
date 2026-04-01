#ifndef FILESERVICEDATABASE_H
#define FILESERVICEDATABASE_H

#include <filesystem>
#include <list>
#include <memory>
#include <mutex>
#include <span>
#include <unordered_map>

#include "types.hpp"

namespace FileService
{
    class SynchronizedOStream;

    class FileServiceDatabase
    {
        private:
            std::recursive_mutex mutable mutex;

            bool overwrite         = false;
            bool createDirectories = false;
            bool dryMode           = false;

            std::filesystem::path inputBasePath;
            std::filesystem::path outputBasePath;

            std::list<FileService::CreatedFileInfo> createdFileInfo;
            std::unordered_map<std::filesystem::path, std::unique_ptr<SynchronizedOStream>> oStreams;

        public:
            FileServiceDatabase();

            bool getOverwrite() const;
            void setOverwrite(bool newOverwrite);

            bool getCreateDirectories() const;
            void setCreateDirectories(bool newCreateDirectories);

            bool getDryMode() const;
            void setDryMode(bool newDryMode);

            const std::filesystem::path& getInputBasePath() const;
            void setInputBasePath(const std::filesystem::path& newInputBasePath);

            const std::filesystem::path& getOutputBasePath() const;
            void setOutputBasePath(const std::filesystem::path& newBase);

            SynchronizedOStream& getOrCreateStream(const std::filesystem::path& filename);
            std::ifstream getReadStream(const std::filesystem::path& filename);

            const std::list<FileService::CreatedFileInfo>& getCreatedFileInfo() const;
            void addCreatedFile(const std::filesystem::path& filename, const bool overwritten);
    };
}

#endif // FILESERVICEDATABASE_H
