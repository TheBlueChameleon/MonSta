#ifndef IVERSIONSERVICE_H
#define IVERSIONSERVICE_H

#include <Version.hpp>

struct IVersionService
{
    bool (*const equal)(const Version& lhs, const Version& rhs);
    bool (*const notEqual)(const Version& lhs, const Version& rhs);
    bool (*const lessThan)(const Version& lhs, const Version& rhs);
    bool (*const lessOrEqual)(const Version& lhs, const Version& rhs);
    bool (*const greaterThan)(const Version& lhs, const Version& rhs);
    bool (*const greaterOrEqual)(const Version& lhs, const Version& rhs);

    // TODO: not yet ABI hardened
    std::string(*const to_string)(const Version& v);
};

#endif // IVERSIONSERVICE_H
