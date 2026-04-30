#ifndef MEMORYSERVICE_HPP
#define MEMORYSERVICE_HPP

#include <span>
#include <string>

#include <services/IMemoryService.hpp>

namespace MemoryService
{
    IMemoryService exportService();

    IMemoryService::String          allocateString(const size_t size);
    IMemoryService::StringArray     allocateStringArray(const size_t size);
    IMemoryService::StringViewArray allocateStringViewArray(const size_t size);

    IMemoryService::String          copy(const std::string_view            view);
    IMemoryService::StringArray     copy(const std::span<std::string_view> view);
    IMemoryService::StringArray     copy(const std::span<std::string>&     view);
    IMemoryService::StringView      wrap(const std::string_view            view);
    IMemoryService::StringViewArray wrap(const std::span<std::string_view> view);
    IMemoryService::StringViewArray wrap(const std::span<std::string>&     view);

    void free(IMemoryService::String& data);
    void free(IMemoryService::StringArray& data);
    void free(IMemoryService::StringViewArray& data);
}

#endif // MEMORYSERVICE_HPP
