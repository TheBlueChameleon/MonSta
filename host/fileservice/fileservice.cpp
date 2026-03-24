#include <algorithm>
#include <fstream>

#include "../logging/loggerservice.hpp"

#include "fileservice.hpp"
#include "fileservicedb.hpp"
#include "stdoutpseudofile.hpp"

namespace FileService
{
    static const std::set<std::string> specialNames = {STDOUT};

    static bool isSpecialPath(const std::filesystem::path& path)
    {
        return FileService::getSpecialNames().contains(path.c_str());
    }

    static bool containsSpecialPath(const std::filesystem::path& path)
    {
        return std::any_of(path.begin(), path.end(), isSpecialPath);
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

    static std::unique_ptr<std::ostream> getSpecialStream(const char* const specialName, const std::string& filename)
    {
        // TODO: switch-like on available specialNames
        return std::make_unique<StdOutPseudoFile>(filename);

        // "default case"
        return nullptr;
    }

    static std::unique_ptr<std::ostream> getStream(const std::filesystem::__cxx11::path& filename, FileServiceDatabaseAccess& access)
    {
        if (isSpecialPath(access.getBase()))
        {
            return getSpecialStream(STDOUT, filename);
        }

        if (isSpecialPath(filename))
        {
            return getSpecialStream(STDOUT, STDOUT);
        }

        const std::filesystem::path resolved = std::filesystem::weakly_canonical(access.getBase() / filename);
        const bool exists = std::filesystem::exists(resolved);

        // TODO: this does not catch "contains special path"
        if (access.getDryMode())
        {
            access.addCreatedFile(resolved, exists);
            return nullptr;
        }

        LoggerService::traceF("Attempting to create '{}'", resolved.c_str());

        if (!maybeMakeDirectoriesOrLog(resolved.parent_path(), access.getCreateDirectories()))
        {
            return nullptr;
        }

        if (exists && ! access.getOverwrite())
        {
            LoggerService::errorF("Could not open '{}': file/directory already exists!", filename.c_str());
            return nullptr;
        }

        auto result = std::make_unique<std::ofstream>(resolved,
                                                      std::ios_base::out | std::ios_base::binary
                                                     );
        if (result->is_open())
        {
            access.addCreatedFile(resolved, exists);
        }
        else
        {
            LoggerService::errorF("Could not open '{}': file system error", filename.c_str());
            return nullptr;
        }

        return result;
    }

    const std::set<std::string>& getSpecialNames()
    {
        return specialNames;
    }

    bool getOverwrite()
    {
        return FileServiceDatabaseAccess().getOverwrite();
    }

    void setOverwrite(bool newOverwrite)
    {
        FileServiceDatabaseAccess().setOverwrite(newOverwrite);
    }

    bool getCreateDirectories()
    {
        return FileServiceDatabaseAccess().getCreateDirectories();
    }

    void setCreateDirectories(bool newCreateDirectories)
    {
        FileServiceDatabaseAccess().setCreateDirectories(newCreateDirectories);
    }

    bool getDryMode()
    {
        return FileServiceDatabaseAccess().getDryMode();
    }

    void setDryMode(bool newDryMode)
    {
        FileServiceDatabaseAccess().setDryMode(newDryMode);
    }

    std::filesystem::__cxx11::path getBase()
    {
        return FileServiceDatabaseAccess().getBase();
    }

    const char* const getBase_cstr()
    {
        return getBase().c_str();
    }

    void setBase(const std::filesystem::__cxx11::path& newBase)
    {
        if (maybeMakeDirectoriesOrLog(newBase, getCreateDirectories()))
        {
            FileServiceDatabaseAccess().setBase(newBase);
        }
    }

    void setBase_cstr(const char* const newBase)
    {
        setBase(newBase);
    }

    void write(const std::filesystem::__cxx11::path& filename, const std::string& content)
    {
        write_cstr(filename.c_str(), content.c_str());
    }

    void write_cstr(const char* const filename, const char* const content)
    {
        auto access = FileServiceDatabaseAccess();
        std::unique_ptr<std::ostream> ptr = getStream(filename, access);
        if (ptr.get() == nullptr)
        {
            return;
        }
        std::ostream& stream = *ptr;
        stream << content;
    }

    void writeBinary(const std::filesystem::__cxx11::path& filename, const std::span<const std::byte> data)
    {
        writeBinary_cstr(filename.c_str(), data.data(), data.size());
    }

    void writeBinary_cstr(const char* const filename, const void* const data, size_t length)
    {
        auto access = FileServiceDatabaseAccess();
        std::unique_ptr<std::ostream> ptr = getStream(filename, access);
        if (ptr.get() == nullptr)
        {
            return;
        }
        std::ostream& stream = *ptr;
        stream.write(reinterpret_cast<const char*>(data), length);
    }

    const std::list<CreatedFileInfo> getCreatedFileInfo()
    {
        return FileServiceDatabaseAccess().getCreatedFileInfo();
    }
}
