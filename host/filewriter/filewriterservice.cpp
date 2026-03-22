#include <cstring>
#include <fstream>

#include "../api/loggerservice.hpp"

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

    std::filesystem::path resolved = getBase() / filename;
    LoggerService::traceF(
        "Attempting to write '{}' ~ exists: {}",
        resolved.c_str(),
        std::filesystem::exists(resolved)
    );
    if (std::filesystem::exists(resolved) && ! getOverwrite())
    {
        LoggerService::errorF("Could not write '{}': file/directory already exists!", filename.c_str());
        return nullptr;
    }

    return std::make_unique<std::ofstream>(resolved,
                                           std::ios_base::out | std::ios_base::binary
                                          );
}

