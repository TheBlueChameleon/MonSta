#ifndef IFILESERVICE_H
#define IFILESERVICE_H

#include <stddef.h>

struct IFileService
{
    struct FileContents
    {
        char*  data;
        size_t size;
    };

    const char* const(*getInputBase)();
    const char* const(*getOutputBase)();

    FileContents(*read)(const char* const filename);
    void(*freeFileContents)(FileContents*);

    void (*write)(const char* const filename, const char* const content);
    void (*writeBinary)(const char* const filename, const void* const data, size_t length);
};

#endif // IFILESERVICE_H
