#ifndef FILEWRITERSERVICE_H
#define FILEWRITERSERVICE_H

#include <filesystem>
#include <list>
#include <memory>
#include <set>
#include <span>

class FileWriterService
{
    public:
        struct CreatedFileInfo
        {
            std::filesystem::path filename;
            bool                  overwritten;
        };

        static constexpr auto STDOUT = ":stdout:";

    private:
        static FileWriterService instance;
        static const std::set<std::string> specialNames;

        std::filesystem::path base;
        bool overwrite = false;
        bool createDirectories = false;
        bool dryMode = false;

        std::list<CreatedFileInfo> createdFileInfo;

    protected:
        FileWriterService();

    public:
        static FileWriterService getInstance();
        static const std::set<std::string>& getSpecialNames();

        static bool getOverwrite();
        static void setOverwrite(bool newOverwrite);

        static bool getCreateDirectories();
        static void setCreateDirectories(bool newCreateDirectories);

        static bool getDryMode();
        static void setDryMode(bool newDryMode);

        static std::filesystem::path getBase();
        static const char* const getBase_cstr();

        static void setBase(const std::filesystem::path& newBase);
        static void setBase_cstr(const char* const newBase);

        static void write(const std::filesystem::path& filename, const std::string& content);
        static void write_cstr(const char* const filename, const char* const content);

        static void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data);
        static void writeBinary_cstr(const char* const filename, const void* const data, size_t length);

        static const std::unique_ptr<std::ostream> getStream(const std::filesystem::path& filename);

        static const std::list<CreatedFileInfo> getCreatedFileInfo();
};

#endif // FILEWRITERSERVICE_H
