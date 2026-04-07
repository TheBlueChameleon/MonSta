#ifndef FILESERVICEOPERATIONS_H
#define FILESERVICEOPERATIONS_H

#include <filesystem>

namespace FileService
{
    enum class OutputStreamType
    {
        REGULAR,
        STDOUT,
        DEBUG,
        NULLSTREAM,
        INVALID
    };

    OutputStreamType outputStreamTypeFromFileName(const std::string_view filename);

    std::pair<OutputStreamType, std::filesystem::path> getOutputStreamTypeAndResidualFilename(const std::filesystem::path& path);

    bool makeDirectoriesOrLog(const std::filesystem::path& path, bool createDirectories);

    std::pair<std::unique_ptr<std::ostream>, bool> createStream(
        const std::filesystem::path& path,
        const bool createDirectories,
        const bool overwrite
    );

    size_t getFileSize(std::ifstream& stream);
}

#endif // FILESERVICEOPERATIONS_H
