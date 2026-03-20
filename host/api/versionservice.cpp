#include <sstream>

#include "versionservice.hpp"

// ========================================================================== //
// proper implementations

bool VersionService::equal(const Version& lhs, const Version& rhs)
{
        // *INDENT-OFF*
        if (lhs.major != rhs.major) return false;
        if (lhs.minor != rhs.minor) return false;
        if (lhs.patch != rhs.patch) return false;
        if (lhs.build != rhs.build) return false;
        // *INDENT-ON*

    return true;
}

bool VersionService::notEqual(const Version& lhs, const Version& rhs)
{
    return !equal(lhs, rhs);
}

bool VersionService::lessThan(const Version& lhs, const Version& rhs)
{
        // *INDENT-OFF*
        if      (lhs.major < rhs.major) return true;
        else if (lhs.major > rhs.major) return false;

        if      (lhs.minor < rhs.minor) return true;
        else if (lhs.minor > rhs.minor) return false;

        if      (lhs.patch < rhs.patch) return true;
        else if (lhs.patch > rhs.patch) return false;

        if      (lhs.build < rhs.build) return true;
        else if (lhs.build > rhs.build) return false;
        // *INDENT-ON*

    return false;
}

bool VersionService::lessOrEqual(const Version& lhs, const Version& rhs)
{
    return lessThan(lhs, rhs) || equal(lhs, rhs);
}

bool VersionService::greaterThan(const Version& lhs, const Version& rhs)
{
    return !lessOrEqual(lhs, rhs);
}

bool VersionService::greaterOrEqual(const Version& lhs, const Version& rhs)
{
    return !lessThan(lhs, rhs);
}

std::ostream& VersionService::streamInto(std::ostream& os, const Version& v)
{
    return os << v.major << "." << v.minor << "." << v.patch << "." << v.build;
}

std::string VersionService::to_string(const Version& v)
{
    std::stringstream s;
    streamInto(s, v);
    return s.str();
}

// ========================================================================== //
// operator redirects

bool operator==(const Version& lhs, const Version& rhs)
{
    return VersionService::equal(lhs, rhs);
}

bool operator!=(const Version& lhs, const Version& rhs)
{
    return VersionService::notEqual(lhs, rhs);
}
bool operator<(const Version& lhs, const Version& rhs)
{
    return VersionService::lessThan(lhs, rhs);
}

bool operator<=(const Version& lhs, const Version& rhs)
{
    return VersionService::lessOrEqual(lhs, rhs);
}

bool operator> (const Version& lhs, const Version& rhs)
{
    return VersionService::greaterThan(lhs, rhs);
}

bool operator>=(const Version& lhs, const Version& rhs)
{
    return VersionService::greaterOrEqual(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const Version& v)
{
    return VersionService::streamInto(os, v);
}
