#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <filesystem>
#include <list>
#include <memory>
#include <set>
#include <span>

#include <IFileService.hpp>

#include "types.hpp"

namespace FileService
{
    // TODO: add NULLFILE = ":null:";
    static constexpr auto STDOUT = ":stdout:";

    bool getOverwrite();
    void setOverwrite(bool newOverwrite);

    bool getCreateDirectories();
    void setCreateDirectories(bool newCreateDirectories);

    bool getDryMode();
    void setDryMode(bool newDryMode);

    std::filesystem::path getInputBasePath();
    const char* const getInputBasePath_cstr();

    std::filesystem::path getOutputBasePath();
    const char* const getOutputBasePath_cstr();

    void setInputBasePath(const std::filesystem::path& newBase);
    void setInputBasePath_cstr(const char* const newBase);

    void setOutputBasePath(const std::filesystem::path& newBase);
    void setOutputBasePath_cstr(const char* const newBase);

    void write(const std::filesystem::path& filename, const std::string& content);
    void write_cstr(const char* const filename, const char* const content);

    void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data);
    void writeBinary_cstr(const char* const filename, const void* const data, size_t length);

    std::string  read(const std::filesystem::path& filename);
    IFileService::FileContents read_cstr(const char* const filename);
    void freeFileContents(IFileService::FileContents *fileContents);

    const std::list<CreatedFileInfo> getCreatedFileInfo();
}

#endif // FILESERVICE_H
