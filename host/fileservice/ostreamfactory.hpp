#ifndef OSTREAMFACTORY_HPP
#define OSTREAMFACTORY_HPP

#include <filesystem>
#include <utility>

namespace  FileService
{
    static constexpr auto STDOUT = ":stdout:";

    enum class TargetStreamType
    {
        REGULAR,
        STDOUT,
        INVALID
    };

    TargetStreamType getTargetStreamType(const std::filesystem::path& path);

    std::pair<std::unique_ptr<std::ostream>, bool> createStream(const std::filesystem::path& path);
}

#endif // OSTREAMFACTORY_HPP
