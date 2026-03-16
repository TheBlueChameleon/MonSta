#ifndef VERSIONUTILS_HPP
#define VERSIONUTILS_HPP

#include <Version.hpp>

namespace VersionUtils
{
    bool equal(const Version& lhs, const Version& rhs);
    bool notEqual(const Version& lhs, const Version& rhs);
    bool lessThan(const Version& lhs, const Version& rhs);
    bool lessOrEqual(const Version& lhs, const Version& rhs);
    bool greaterThan(const Version& lhs, const Version& rhs);
    bool greaterOrEqual(const Version& lhs, const Version& rhs);

    std::ostream& streamInto(std::ostream& os, const Version& v);
    std::string to_string(const Version& v);
}

bool operator==(const Version& lhs, const Version& rhs);
bool operator!=(const Version& lhs, const Version& rhs);
bool operator< (const Version& lhs, const Version& rhs);
bool operator<=(const Version& lhs, const Version& rhs);
bool operator> (const Version& lhs, const Version& rhs);
bool operator>=(const Version& lhs, const Version& rhs);

std::ostream& operator<<(std::ostream& os, const Version& v);

#endif // VERSIONUTILS_HPP
