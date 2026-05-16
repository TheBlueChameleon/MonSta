#include "errorservice.hpp"
#include "services.hpp"
#include "fileservice.hpp"

using namespace Services;
using namespace ErrorService;

namespace FileService
{
    const std::filesystem::path getInputBase()
    {
        auto result = fileService().getInputBase();
        rethrowHostError();
        return result;
    }

    const std::filesystem::path getOutputBase()
    {
        auto result = fileService().getOutputBase();
        rethrowHostError();
        return result;
    }

    MemoryService::String read(const std::filesystem::path& filename)
    {
        auto result = fileService().read(filename.c_str());
        rethrowHostError();
        return result;
    }

    void write(const std::filesystem::path& filename, const std::string_view content)
    {
        fileService().write(filename.c_str(), content.data());
        rethrowHostError();
    }

    void writeBinary(const std::filesystem::path& filename, const std::span<const std::byte> data)
    {
        fileService().writeBinary(filename.c_str(), data.data(), data.size());
        rethrowHostError();
    }

}
