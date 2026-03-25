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

    struct FileContents
    {
        char*  data;
        size_t size;
    };
}

#endif // TYPES_H
