#include <algorithm>
#include <cstring>
#include <fstream>
#include <set>
#include <string>
using namespace std::string_literals;

#include "../errors.hpp"

#include "../logging/loggerservice.hpp"

#include "fileservice.hpp"
#include "fileserviceoperations.hpp"
#include "stdoutpseudofile.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    static const std::set<std::string> specialNames = {STDOUT};

    static bool pathEqualsCString(const std::filesystem::__cxx11::path& path, const char* const cstring)
    {
        return std::strcmp(path.begin()->c_str(), cstring) == 0;
    }

    bool isSpecialPath(const std::filesystem::path& path)
    {
        return specialNames.contains(path.c_str());
    }

    bool containsSpecialPath(const std::filesystem::path& path)
    {
        return std::any_of(path.begin(), path.end(), isSpecialPath);
    }

    TargetStreamType getTargetStreamType(const std::filesystem::__cxx11::path& path)
    {
        if (path.empty())
        {
            return TargetStreamType::INVALID;
        }

        if (pathEqualsCString(path, STDOUT))
        {
            return TargetStreamType::STDOUT;
        }

        if (pathEqualsCString(path.filename(), STDOUT))
        {
            return TargetStreamType::STDOUT;
        }

        return TargetStreamType::REGULAR;
    }

    bool makeDirectoriesOrLog(const std::filesystem::path& path, bool createDirectories)
    {
        if (path.empty())
        {
            return true;
        }

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

    std::pair<std::unique_ptr<std::ostream>, bool> createStream(
        const std::filesystem::__cxx11::path& path,
        const bool createDirectories,
        const bool overwrite
    )
    {
        LoggerService::traceF("got {}", path.c_str());
        const TargetStreamType type = getTargetStreamType(path);
        LoggerService::traceF("made {}", static_cast<int>(type));

        const auto parent = path.parent_path();
        const bool parentDirAsserted = makeDirectoriesOrLog(parent, createDirectories);
        if (!parentDirAsserted)
        {
            LoggerService::errorF("Could not create directory '{}'",
                                  parent.c_str()
                                 );
            return std::make_pair(nullptr, false);
        }

        switch (type)
        {
            case TargetStreamType::REGULAR:
                {
                    const bool exists = std::filesystem::exists(path);
                    if (exists)
                    {
                        if (!overwrite)
                        {
                            LoggerService::errorF("Could not create file '{}': file already exists",
                                                  path.c_str()
                                                 );
                            return std::make_pair(nullptr, false);
                        }
                    }

                    std::ofstream* stream = new std::ofstream(path);
                    if (!stream->is_open())
                    {
                        LoggerService::errorF("Could not create file '{}': file system error",
                                              path.c_str()
                                             );
                        return std::make_pair(nullptr, false);
                    }
                    return std::make_pair(
                               std::unique_ptr<std::ostream>(stream),
                               exists
                           );
                }

            case TargetStreamType::STDOUT:
                return std::make_pair(
                           std::make_unique<StdOutPseudoFile>(path),
                           false
                       );

            case TargetStreamType::INVALID:
                return std::make_pair(nullptr, false);
        }

        throw IllegalStateException("Unknown target type: '"s + path.c_str() + "'");
    }
}
