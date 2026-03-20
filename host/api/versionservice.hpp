#ifndef VERSIONSERVICE_H
#define VERSIONSERVICE_H

#include <Version.hpp>

struct VersionService
{
    static bool equal(const Version& lhs, const Version& rhs);
    static bool notEqual(const Version& lhs, const Version& rhs);
    static bool lessThan(const Version& lhs, const Version& rhs);
    static bool lessOrEqual(const Version& lhs, const Version& rhs);
    static bool greaterThan(const Version& lhs, const Version& rhs);
    static bool greaterOrEqual(const Version& lhs, const Version& rhs);

    static std::ostream& streamInto(std::ostream& os, const Version& v);
    static std::string to_string(const Version& v);
};

bool operator==(const Version& lhs, const Version& rhs);
bool operator!=(const Version& lhs, const Version& rhs);
bool operator< (const Version& lhs, const Version& rhs);
bool operator<=(const Version& lhs, const Version& rhs);
bool operator> (const Version& lhs, const Version& rhs);
bool operator>=(const Version& lhs, const Version& rhs);

std::ostream& operator<<(std::ostream& os, const Version& v);

#endif // VERSIONSERVICE_H
