#ifndef VERSIONSERVICE_HPP
#define VERSIONSERVICE_HPP

#include "services/memoryservice.hpp"

namespace VersionService
{
    bool equal(const Version lhs, const Version rhs);
    bool notEqual(const Version lhs, const Version rhs);
    bool lessThan(const Version lhs, const Version rhs);
    bool lessOrEqual(const Version lhs, const Version rhs);
    bool greaterThan(const Version lhs, const Version rhs);
    bool greaterOrEqual(const Version lhs, const Version rhs);

    MemoryService::String to_string(const Version v);
}

#endif // VERSIONSERVICE_HPP
