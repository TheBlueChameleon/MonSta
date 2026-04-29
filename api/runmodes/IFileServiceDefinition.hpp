#ifndef IFILESERVICEDEFINITION_HPP
#define IFILESERVICEDEFINITION_HPP

struct IFileServiceDefinition
{
    const bool overwrite;
    const bool createDirectories;
    const bool dryMode;

    const char* const inputDirectory;
    const char* const outputDirectory;
    const char* const engine;
};

#endif // IFILESERVICEDEFINITION_HPP
