#ifndef VERSIONSERVICE_HPP
#define VERSIONSERVICE_HPP

#include <compare>
#include <string>

#include <Version.hpp>

#include <services/IVersionService.hpp>

namespace VersionService
{
    IVersionService exportService();

    std::string to_string(const Version& v);
}

std::strong_ordering operator<=>(const Version& lhs, const Version& rhs);
bool operator==(const Version& lhs, const Version& rhs);
bool operator!=(const Version& lhs, const Version& rhs);

std::ostream& operator<<(std::ostream& os, const Version& v);

#endif // VERSIONSERVICE_HPP
