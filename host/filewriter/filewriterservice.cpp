#include <cstring>
#include <fstream>

#include "../logging/loggerservice.hpp"

#include "filewriterservice.hpp"
#include "stdoutpseudofile.hpp"

FileWriterService FileWriterService::instance;

FileWriterService::FileWriterService() :
    base(std::filesystem::current_path())
{}

bool FileWriterService::getOverwrite()
{
    return instance.overwrite;
}

void FileWriterService::setOverwrite(bool newOverwrite)
{
    instance.overwrite = newOverwrite;
}

bool FileWriterService::getCreateDirectories()
{
    return instance.createDirectories;
}

void FileWriterService::setCreateDirectories(bool newCreateDirectories)
{
    instance.createDirectories = newCreateDirectories;
}

bool FileWriterService::getDryMode()
{
    return instance.dryMode;
}

void FileWriterService::setDryMode(bool newDryMode)
{
    instance.dryMode = newDryMode;
}

FileWriterService FileWriterService::getInstance()
{
    return instance;
}

std::filesystem::path FileWriterService::getBase()
{
    return instance.base;
}

const char* const FileWriterService::getBase_cstr()
{
    return getBase().c_str();
}

void FileWriterService::setBase(const std::filesystem::path& newBase)
{
    instance.base = newBase;
}

void FileWriterService::setBase_cstr(const char* const newBase)
{
    setBase(newBase);
}

void FileWriterService::write(const std::filesystem::__cxx11::path& filename, const std::string& content)
{
    write_cstr(filename.c_str(), content.c_str());
}

void FileWriterService::write_cstr(const char* const filename, const char* const content)
{
    auto ptr = getStream(filename);
    if (ptr.get() == nullptr)
    {
        return;
    }
    std::ostream& stream = *ptr;
    stream << content;
}

void FileWriterService::writeBinary(const std::filesystem::__cxx11::path& filename, const std::span<const std::byte> data)
{
    writeBinary_cstr(filename.c_str(), data.data(), data.size());
}

void FileWriterService::writeBinary_cstr(const char* const filename, const void* const data, size_t length)
{
    std::unique_ptr<std::ostream> ptr = getStream(filename);
    if (ptr.get() == nullptr)
    {
        return;
    }
    std::ostream& stream = *ptr;
    stream.write(reinterpret_cast<const char*>(data), length);
}

const std::unique_ptr<std::ostream> FileWriterService::getStream(const std::filesystem::__cxx11::path& filename)
{
    if (std::strcmp(getBase().c_str(), STDOUT) == 0)
    {
        return std::make_unique<StdOutPseudoFile>(filename.c_str());
    }

    if (std::strcmp(filename.c_str(), STDOUT) == 0)
    {
        return std::make_unique<StdOutPseudoFile>(STDOUT);
    }

    const std::filesystem::path resolved = std::filesystem::weakly_canonical(getBase() / filename);
    const std::filesystem::path parent = resolved.parent_path();
    const bool exists = std::filesystem::exists(resolved);
    const bool parentExists = std::filesystem::exists(parent);

    if (getDryMode())
    {
        instance.createdFileInfo.emplace_back(resolved, exists);
        return nullptr;
    }

    if (getCreateDirectories() && !parentExists)
    {
        try
        {
            std::filesystem::create_directories(parent);
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            LoggerService::errorF("Could not create directory '{}': {}",
                                  parent.c_str(),
                                  e.what()
                                 );
            return nullptr;
        }
    }

    LoggerService::traceF("Attempting to open '{}'", resolved.c_str());
    if (exists && ! getOverwrite())
    {
        LoggerService::errorF("Could not open '{}': file/directory already exists!", filename.c_str());
        return nullptr;
    }

    auto result = std::make_unique<std::ofstream>(resolved,
                                                  std::ios_base::out | std::ios_base::binary
                                                 );
    if (result->is_open())
    {
        instance.createdFileInfo.emplace_back(resolved, exists);
    }
    else
    {
        LoggerService::errorF("Could not open '{}': file system error", filename.c_str());
        return nullptr;
    }

    return result;
}

const std::list<FileWriterService::CreatedFileInfo> FileWriterService::getCreatedFileInfo()
{
    return instance.createdFileInfo;
}
