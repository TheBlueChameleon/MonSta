#ifndef IFILESERVICE_H
#define IFILESERVICE_H

struct IFileServie
{
    const char* const(*getBase)();
    void (*setBase)(const char* const newBase);

    void (*write)(const char* const filename, const char* const content);
    void (*writeBinary)(const char* const filename, const void* const data, size_t length);
};

#endif // IFILESERVICE_H
