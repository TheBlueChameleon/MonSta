#ifndef IFILESERVICE_H
#define IFILESERVICE_H

struct IFileService
{
    struct FileContents
    {
        char*  data;
        size_t size;
    };

    const char* const(*getInputBase)();
    void (*setInputBase)(const char* const newBase);

    const char* const(*getOutputBase)();
    void (*setOutputBase)(const char* const newBase);

    FileContents(*read)(const char* const filename);
    void(*freeFileContents)(FileContents*);

    void (*write)(const char* const filename, const char* const content);
    void (*writeBinary)(const char* const filename, const void* const data, size_t length);
};

#endif // IFILESERVICE_H
