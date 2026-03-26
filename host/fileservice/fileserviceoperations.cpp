#include <algorithm>
#include <cstring>
#include <fstream>
#include <set>
#include <string>
using namespace std::string_literals;

#include "../errors.hpp"

#include "../logging/loggerservice.hpp"

#include "debugstream.hpp"
#include "fileservice.hpp"
#include "fileserviceoperations.hpp"
#include "nullstream.hpp"
#include "stdoutstream.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    static bool equalsCString(const char* const lhs, const char* const rhs)
    {
        return std::strcmp(lhs, rhs) == 0;
    }

    OutputStreamType outputStreamTypeFromCString(const char* const cstring)
    {
        if (equalsCString(cstring, STDOUTSTREAM))
        {
            return OutputStreamType::STDOUT;
        }

        if (equalsCString(cstring, DEBUGSTREAM))
        {
            return OutputStreamType::DEBUG;
        }

        if (equalsCString(cstring, NULLSTREAM))
        {
            return OutputStreamType::NULLSTREAM;
        }

        if (cstring[0] == ':')
        {
            return OutputStreamType::INVALID;
        }

        return OutputStreamType::REGULAR;
    }

    std::pair<OutputStreamType, std::filesystem::__cxx11::path> getOutputStreamTypeAndResidualFilename(const std::filesystem::__cxx11::path& path)
    {
        if (path.empty())
        {
            return {OutputStreamType::INVALID, path};
        }

        OutputStreamType type = OutputStreamType::REGULAR;
        std::filesystem::path residual = path;
        for (const auto element : path)
        {
            const OutputStreamType elementType = outputStreamTypeFromCString(element.c_str());
            if (type == OutputStreamType::REGULAR)
            {
                if (elementType != OutputStreamType::REGULAR)
                {
                    type = elementType;
                    residual = "";
                }
            }
            else
            {
                if (elementType != OutputStreamType::REGULAR)
                {
                    return {OutputStreamType::INVALID, path};
                }
                residual /= element;
            }
        }
        return {type, residual};
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

    static std::pair<std::unique_ptr<std::ostream>, bool> createRegularStream(
        const std::filesystem::__cxx11::path& path,
        const bool createDirectories,
        const bool overwrite
    )
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

        LoggerService::debugF("created file '{}'",
                              path.c_str()
                             );
        return std::make_pair(
                   std::unique_ptr<std::ostream>(stream),
                   exists
               );
    }

    std::pair<std::unique_ptr<std::ostream>, bool> createStream(
        const std::filesystem::__cxx11::path& path,
        const bool createDirectories,
        const bool overwrite
    )
    {
        const auto& [type, residual] = getOutputStreamTypeAndResidualFilename(path);
        const auto  parent = path.parent_path();
        const bool  parentDirAsserted = makeDirectoriesOrLog(parent, createDirectories);
        if (!parentDirAsserted)
        {
            LoggerService::errorF("Could not create directory '{}'",
                                  parent.c_str()
                                 );
            return std::make_pair(nullptr, false);
        }

        switch (type)
        {
            case OutputStreamType::REGULAR:
                return createRegularStream(path, createDirectories, overwrite);

            case OutputStreamType::STDOUT:
                return std::make_pair(
                           std::make_unique<StdOutStream>(residual),
                           false
                       );

            case OutputStreamType::DEBUG:
                return std::make_pair(
                           std::make_unique<DebugStream>(),
                           false
                       );

            case OutputStreamType::NULLSTREAM:
                return std::make_pair(
                           std::make_unique<NullStream>(),
                           false
                       );

            case OutputStreamType::INVALID:
                return std::make_pair(nullptr, false);
        }

        throw IllegalStateException("Unknown target type: '"s + path.c_str() + "'");
    }

    size_t getFileSize(std::ifstream& stream)
    {
        size_t result;

        stream.seekg(0, std::ios::end);
        result = stream.tellg();
        stream.seekg(0);

        return result;
    }
}
