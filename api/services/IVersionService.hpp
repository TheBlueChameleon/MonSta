#ifndef IVERSIONSERVICE_HPP
#define IVERSIONSERVICE_HPP

#include <CallingConventions.hpp>
#include <Version.hpp>

#include <services/IMemoryService.hpp>

struct IVersionService
{
    bool (HOST_API_CALL* const equal)(const Version lhs, const Version rhs);
    bool (HOST_API_CALL* const notEqual)(const Version lhs, const Version rhs);
    bool (HOST_API_CALL* const lessThan)(const Version lhs, const Version rhs);
    bool (HOST_API_CALL* const lessOrEqual)(const Version lhs, const Version rhs);
    bool (HOST_API_CALL* const greaterThan)(const Version lhs, const Version rhs);
    bool (HOST_API_CALL* const greaterOrEqual)(const Version lhs, const Version rhs);

    IMemoryService::MemoryBlock(HOST_API_CALL* const to_string)(const Version v);
};

#endif // IVERSIONSERVICE_HPP
