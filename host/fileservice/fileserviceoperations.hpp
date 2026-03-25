#ifndef FILESERVICEOPERATIONS_H
#define FILESERVICEOPERATIONS_H

#include <filesystem>
#include <utility>

namespace FileService
{
    enum class TargetStreamType
    {
        REGULAR,
        STDOUT,
        INVALID
    };

    bool isSpecialPath(const std::filesystem::path& path);
    bool containsSpecialPath(const std::filesystem::path& path);

    TargetStreamType getTargetStreamType(const std::filesystem::path& path);

    bool makeDirectoriesOrLog(const std::filesystem::path& path, bool createDirectories);

    std::pair<std::unique_ptr<std::ostream>, bool> createStream(
        const std::filesystem::path& path,
        const bool createDirectories,
        const bool overwrite
    );
}

#endif // FILESERVICEOPERATIONS_H
