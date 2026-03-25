#include <cstring>
#include <fstream>
#include <string>
using namespace std::string_literals;

#include "../errors.hpp"

#include "ostreamfactory.hpp"
#include "stdoutpseudofile.hpp"
#include "synchronizedostream.hpp"

namespace FileService
{
    TargetStreamType getTargetStreamType(const std::filesystem::__cxx11::path& path)
    {
        if (path.empty())
        {
            return TargetStreamType::INVALID;
        }

        if (std::strcmp(path.begin()->c_str(), STDOUT) == 0)
        {
            return TargetStreamType::STDOUT;
        }

        if (std::strcmp(path.filename().c_str(), STDOUT) == 0)
        {
            return TargetStreamType::STDOUT;
        }

        return TargetStreamType::REGULAR;
    }

    std::pair<std::unique_ptr<std::ostream>, bool> createStream(const std::filesystem::__cxx11::path& path)
    {
        const TargetStreamType type = getTargetStreamType(path);

        // TODO -c, -o handling

        switch (type)
        {
            case TargetStreamType::REGULAR:
                return std::make_pair(std::make_unique<std::ofstream>(path), true) ;

            case TargetStreamType::STDOUT:
                return std::make_pair(std::make_unique<StdOutPseudoFile>(path), false);

            case TargetStreamType::INVALID:
                return std::make_pair(nullptr, false);
        }

        throw IllegalStateException("Unknown target type: '"s + path.c_str() + "'");
    }

}
