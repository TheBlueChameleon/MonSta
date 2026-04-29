#ifndef FILESERVICE_HPP
#define FILESERVICE_HPP

#include <filesystem>
#include <list>
#include <span>

#include <services/IFileService.hpp>

#include "types.hpp"

namespace FileService
{
    class FileServiceDatabase;

    IFileService exportService();

    FileServiceDatabase& getDatabase();

    bool isSpecialPath(const std::filesystem::path& path);

    bool getOverwrite();
    void setOverwrite(bool newOverwrite);

    bool getCreateDirectories();
    void setCreateDirectories(bool newCreateDirectories);

    bool getDryMode();
    void setDryMode(bool newDryMode);

    std::filesystem::path getInputBasePath();
    std::filesystem::path getOutputBasePath();

    void setInputBasePath(const std::filesystem::path& newBase);
    void setOutputBasePath(const std::filesystem::path& newBase);

    std::ifstream getInputStream(const std::filesystem::path& filename);
    std::string read(const std::filesystem::path& filename);

    void write(const std::filesystem::path& filename, const std::string_view content);
    void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data);

    const std::list<CreatedFileInfo>& getCreatedFileInfo();
}

#endif // FILESERVICE_HPP
