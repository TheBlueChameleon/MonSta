#include <sstream>

#include "versionutils.hpp"

// ========================================================================== //
// proper implementations

namespace VersionUtils
{
    bool equal(const Version& lhs, const Version& rhs)
    {
        // *INDENT-OFF*
        if (lhs.major != rhs.major) return false;
        if (lhs.minor != rhs.minor) return false;
        if (lhs.patch != rhs.patch) return false;
        if (lhs.build != rhs.build) return false;
        // *INDENT-ON*

        return true;
    }

    bool notEqual(const Version& lhs, const Version& rhs)
    {
        return !equal(lhs, rhs);
    }

    bool lessThan(const Version& lhs, const Version& rhs)
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

    bool lessOrEqual(const Version& lhs, const Version& rhs)
    {
        return lessThan(lhs, rhs) || equal(lhs, rhs);
    }

    bool greaterThan(const Version& lhs, const Version& rhs)
    {
        return !lessOrEqual(lhs, rhs);
    }

    bool greaterOrEqual(const Version& lhs, const Version& rhs)
    {
        return !lessThan(lhs, rhs);
    }

    std::ostream& streamInto(std::ostream& os, const Version& v)
    {
        return os << v.major << "." << v.minor << "." << v.patch << "." << v.build;
    }

    std::string to_string(const Version& v)
    {
        std::stringstream s;
        streamInto(s, v);
        return s.str();
    }
}

// ========================================================================== //
// operator redirects

using namespace VersionUtils;

bool operator==(const Version& lhs, const Version& rhs)
{
    return equal(lhs, rhs);
}

bool operator!=(const Version& lhs, const Version& rhs)
{
    return notEqual(lhs, rhs);
}
bool operator<(const Version& lhs, const Version& rhs)
{
    return lessThan(lhs, rhs);
}

bool operator<=(const Version& lhs, const Version& rhs)
{
    return lessOrEqual(lhs, rhs);
}

bool operator> (const Version& lhs, const Version& rhs)
{
    return greaterThan(lhs, rhs);
}

bool operator>=(const Version& lhs, const Version& rhs)
{
    return greaterOrEqual(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const Version& v)
{
    return streamInto(os, v);
}
