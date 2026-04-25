#include "memoryservice/memoryservice.hpp"

#include "versionservice.hpp"
#include "versionservice_dlx.hpp"

namespace VersionService
{
    bool HOST_API_CALL equal_dlx(const Version lhs, const Version rhs)
    {
        return lhs == rhs;
    }

    bool HOST_API_CALL notEqual_dlx(const Version lhs, const Version rhs)
    {
        return lhs != rhs;
    }

    bool HOST_API_CALL lessThan_dlx(const Version lhs, const Version rhs)
    {
        return lhs < rhs;
    }

    bool HOST_API_CALL lessOrEqual_dlx(const Version lhs, const Version rhs)
    {
        return lhs <= rhs;
    }

    bool HOST_API_CALL greaterThan_dlx(const Version lhs, const Version rhs)
    {
        return lhs > rhs;
    }

    bool HOST_API_CALL greaterOrEqual_dlx(const Version lhs, const Version rhs)
    {
        return lhs >= rhs;
    }

    IMemoryService::MemoryBlock HOST_API_CALL to_string_dlx(const Version v)
    {
        std::string foo = VersionService::to_string(v);
        return MemoryService::createFromView(foo);
    }
}
