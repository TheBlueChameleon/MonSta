#ifndef FILEWRITERCONFIG_HPP
#define FILEWRITERCONFIG_HPP

#include <filesystem>
#include <list>
#include <memory>
#include <semaphore>
#include <span>

#include "createdfileinfo.hpp"

class FileWriterConfig
{
    private:
        static FileWriterConfig instance;

        bool overwrite         = false;
        bool createDirectories = false;
        bool dryMode           = false;

        std::filesystem::path base;
        std::list<FileWriterService::CreatedFileInfo> createdFileInfo;
        std::binary_semaphore smph;

        FileWriterConfig();

        friend class FileWriterConfigAccess;
};

class FileWriterConfigAccess
{
    private:
        FileWriterConfig& instance;

    public:
        FileWriterConfigAccess();
        ~FileWriterConfigAccess();

        bool getOverwrite();
        void setOverwrite(bool newOverwrite);

        bool getCreateDirectories();
        void setCreateDirectories(bool newCreateDirectories);

        bool getDryMode();
        void setDryMode(bool newDryMode);

        const std::filesystem::path& getBase();
        void setBase(const std::filesystem::path& newBase);

        const std::list<FileWriterService::CreatedFileInfo>& getCreatedFileInfo();
        void addCreatedFile(const std::filesystem::path& filename, const bool overwritten);
};

#endif // FILEWRITERCONFIG_HPP
