#include <algorithm>
#include <cstring>
#include <fstream>

#include "../logging/loggerservice.hpp"

#include "filewriterservice.hpp"
#include "stdoutpseudofile.hpp"

FileWriterService FileWriterService::instance;
const std::set<std::string> FileWriterService::specialNames = {STDOUT};

static bool isSpecialPath(const std::filesystem::path& path)
{
    return FileWriterService::getSpecialNames().contains(path.c_str());
}

static bool containsSpecialPath(const std::filesystem::path& path)
{
    return std::any_of(path.begin(), path.end(), isSpecialPath);
}

static const std::unique_ptr<std::ostream> getSpecialStream(const char* const specialName, const std::string& filename)
{
    // TODO: switch-like on available specialNames
    return std::make_unique<StdOutPseudoFile>(filename);

    // "default case"
    return nullptr;
}

static bool maybeMakeDirectoriesOrLog(const std::filesystem::path& path, bool createDirectories)
{
    if (isSpecialPath(path))
    {
        return true;
    }

    if (containsSpecialPath(path))
    {
        LoggerService::errorF("Invalid use of reserved symbol in '{}'",
                              path.c_str()
                             );
        return false;
    }

    if (std::filesystem::exists(path))
    {
        return true;
    }

    if (createDirectories)
    {
        try
        {
            std::filesystem::create_directories(path);
            return true;
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            LoggerService::errorF("Could not create directory '{}': {}",
                                  path.c_str(),
                                  e.what()
                                 );
            return false;
        }
    }

    return false;
}

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

const std::set<std::string>& FileWriterService::getSpecialNames()
{
    return FileWriterService::specialNames;
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
    if (maybeMakeDirectoriesOrLog(newBase, getCreateDirectories()))
    {
        instance.base = newBase;
    }
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
    if (isSpecialPath(getBase()))
    {
        return getSpecialStream(STDOUT, filename);
    }

    if (isSpecialPath(filename))
    {
        return getSpecialStream(STDOUT, STDOUT);
    }

    const std::filesystem::path resolved = std::filesystem::weakly_canonical(getBase() / filename);
    const bool exists = std::filesystem::exists(resolved);

    // TODO: this does not catch "contains special path"
    if (getDryMode())
    {
        instance.createdFileInfo.emplace_back(resolved, exists);
        return nullptr;
    }

    LoggerService::traceF("Attempting to create '{}'", resolved.c_str());

    if (!maybeMakeDirectoriesOrLog(resolved.parent_path(), getCreateDirectories()))
    {
        return nullptr;
    }

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
