#ifndef IVERSIONUTILS_HPP
#define IVERSIONUTILS_HPP

#include <Version.hpp>

struct IVersionUtils
{
    bool (*equal)(const Version& lhs, const Version& rhs);
    bool (*notEqual)(const Version& lhs, const Version& rhs);
    bool (*lessThan)(const Version& lhs, const Version& rhs);
    bool (*lessOrEqual)(const Version& lhs, const Version& rhs);
    bool (*greaterThan)(const Version& lhs, const Version& rhs);
    bool (*greaterOrEqual)(const Version& lhs, const Version& rhs);
    std::ostream& (*streamInto)(std::ostream& os, const Version& v);
    std::string(*to_string)(const Version& v);
};

#endif // IVERSIONUTILS_HPP
