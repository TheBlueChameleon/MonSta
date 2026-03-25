#ifndef TYPES_H
#define TYPES_H

#include <filesystem>

namespace FileService
{
    struct CreatedFileInfo
    {
        std::filesystem::path filename;
        bool                  overwritten;
    };
}

#endif // TYPES_H
