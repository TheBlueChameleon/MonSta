#include <format>

#include "memoryservice/memoryservice.hpp"

#include "versionservice.hpp"
#include "versionservice_dlx.hpp"

namespace VersionService
{
    IVersionService exportService()
    {
        return IVersionService(
                   equal_dlx,
                   notEqual_dlx,
                   lessThan_dlx,
                   lessOrEqual_dlx,
                   greaterThan_dlx,
                   greaterOrEqual_dlx,
                   to_string_dlx
               );
    }

    std::string to_string(const Version& v)
    {
        return std::format("{}.{}.{}.{}",
                           v.major, v.minor, v.patch, v.build
                          );
    }
}

// ========================================================================== //
// operators

std::strong_ordering operator<=>(const Version& lhs, const Version& rhs)
{
    // *INDENT-OFF*
    if (lhs.major < rhs.major) {return std::strong_ordering::less;}
    if (lhs.major > rhs.major) {return std::strong_ordering::greater;}

    if (lhs.minor < rhs.minor) {return std::strong_ordering::less;}
    if (lhs.minor > rhs.minor) {return std::strong_ordering::greater;}

    if (lhs.patch < rhs.patch) {return std::strong_ordering::less;}
    if (lhs.patch > rhs.patch) {return std::strong_ordering::greater;}

    if (lhs.build < rhs.build) {return std::strong_ordering::less;}
    if (lhs.build > rhs.build) {return std::strong_ordering::greater;}
    // *INDENT-ON*

    return std::strong_ordering::equal;
}

bool operator==(const Version& lhs, const Version& rhs)
{
    return (lhs <=> rhs) == std::strong_ordering::equal;
}

bool operator!=(const Version& lhs, const Version& rhs)
{
    return (lhs <=> rhs) != std::strong_ordering::equal;
}

std::ostream& operator<<(std::ostream& os, const Version& v)
{
    return os << VersionService::to_string(v);
}
