#ifndef IFILEWRITERSERVICE_HPP
#define IFILEWRITERSERVICE_HPP

struct IFileWriterServie
{
    const char* const(*getBase)();
    void (*setBase)(const char* const newBase);

    void (*write)(const char* const filename, const char* const content);
    void (*writeBinary)(const char* const filename, const void* const data, size_t length);
};

#endif // IFILEWRITERSERVICE_HPP
