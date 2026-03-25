#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <filesystem>
#include <list>
#include <memory>
#include <set>
#include <span>

#include "createdfileinfo.hpp"

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

    std::filesystem::path getOutputBasePath();
    const char* const getOutputBasePath_cstr();

    void setOutputBasePath(const std::filesystem::path& newBase);
    void setOutputBasePath_cstr(const char* const newBase);

    void write(const std::filesystem::path& filename, const std::string& content);
    void write_cstr(const char* const filename, const char* const content);

    void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data);
    void writeBinary_cstr(const char* const filename, const void* const data, size_t length);

    const std::list<CreatedFileInfo> getCreatedFileInfo();
}

#endif // FILESERVICE_H
