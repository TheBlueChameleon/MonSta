#ifndef TYPES_HPP
#define TYPES_HPP

#include <filesystem>

namespace FileService
{
    struct CreatedFileInfo
    {
        std::filesystem::path filename;
        bool                  overwritten;
    };
}

#endif // TYPES_HPP
