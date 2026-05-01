#include "errorservice.hpp"
#include "services.hpp"
#include "versionservice.hpp"

using namespace Services;
using namespace ErrorService;

namespace VersionService
{
    bool equal(const Version lhs, const Version rhs)
    {
        const auto result = versionService().equal(lhs, rhs);
        rethrowHostError();
        return result;
    }

    bool notEqual(const Version lhs, const Version rhs)
    {
        const auto result = versionService().notEqual(lhs, rhs);
        rethrowHostError();
        return result;
    }

    bool lessThan(const Version lhs, const Version rhs)
    {
        const auto result = versionService().lessThan(lhs, rhs);
        rethrowHostError();
        return result;
    }

    bool lessOrEqual(const Version lhs, const Version rhs)
    {
        const auto result = versionService().lessOrEqual(lhs, rhs);
        rethrowHostError();
        return result;
    }

    bool greaterThan(const Version lhs, const Version rhs)
    {
        const auto result = versionService().greaterThan(lhs, rhs);
        rethrowHostError();
        return result;
    }

    bool greaterOrEqual(const Version lhs, const Version rhs)
    {
        const auto result = versionService().greaterOrEqual(lhs, rhs);
        rethrowHostError();
        return result;
    }

    MemoryService::String to_string(const Version v)
    {
        const auto result = versionService().to_string(v);
        rethrowHostError();
        return result;
    }

}
