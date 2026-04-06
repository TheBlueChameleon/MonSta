#include "services.hpp"
#include "fileservice.hpp"

namespace FileService
{
    const std::filesystem::__cxx11::path getInputBase()
    {
        return fileService().getInputBase();
    }

    const std::filesystem::__cxx11::path getOutputBase()
    {
        return fileService().getOutputBase();
    }

    IMemoryService::MemoryBlock read(const std::filesystem::__cxx11::path& filename)
    {
        return fileService().read(filename.c_str());
    }

    void write(const std::filesystem::__cxx11::path& filename, const std::string_view content)
    {
        return fileService().write(filename.c_str(), content.data());
    }

    void writeBinary(const std::filesystem::__cxx11::path& filename, const std::span<const std::byte> data)
    {
        return fileService().writeBinary(filename.c_str(), data.data(), data.size());
    }

}
