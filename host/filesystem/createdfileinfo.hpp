#ifndef CREATEDFILEINFO_HPP
#define CREATEDFILEINFO_HPP

#include <filesystem>

namespace FileWriterService
{
    struct CreatedFileInfo
    {
        std::filesystem::path filename;
        bool                  overwritten;
    };
}

#endif // CREATEDFILEINFO_HPP
