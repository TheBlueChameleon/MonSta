#ifndef FILESERVICE_HPP
#define FILESERVICE_HPP

#include <filesystem>
#include <span>
#include <string_view>

#include <services/IFileService.hpp>
#include <services/IMemoryService.hpp>

namespace FileService
{
    const std::filesystem::path getInputBase();
    const std::filesystem::path getOutputBase();

    // TODO: wrapper with std::shared_ptr?
    IMemoryService::MemoryBlock read(const std::filesystem::path& filename);

    void write(const std::filesystem::path& filename, const std::string_view content);
    void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data);
}

#endif // FILESERVICE_HPP
