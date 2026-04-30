#ifndef VERSIONSERVICE_DLX_HPP
#define VERSIONSERVICE_DLX_HPP

#include <CallingConventions.hpp>
#include <Version.hpp>

#include <services/IMemoryService.hpp>

namespace VersionService
{
    bool HOST_API_CALL equal_dlx(const Version lhs, const Version rhs);
    bool HOST_API_CALL notEqual_dlx(const Version lhs, const Version rhs);
    bool HOST_API_CALL lessThan_dlx(const Version lhs, const Version rhs);
    bool HOST_API_CALL lessOrEqual_dlx(const Version lhs, const Version rhs);
    bool HOST_API_CALL greaterThan_dlx(const Version lhs, const Version rhs);
    bool HOST_API_CALL greaterOrEqual_dlx(const Version lhs, const Version rhs);

    IMemoryService::String HOST_API_CALL to_string_dlx(const Version v);
}

#endif // VERSIONSERVICE_DLX_HPP
