#ifndef FILESERVICEADAPTER_HPP
#define FILESERVICEADAPTER_HPP

#include <filesystem>
#include <string>

namespace FileServiceAdapter
{
    std::string getDebugStreamContent();
    std::string getDebugStreamContent(const std::filesystem::path& path);
}

#endif // FILESERVICEADAPTER_HPP
