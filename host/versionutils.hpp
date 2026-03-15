#ifndef VERSIONUTILS_HPP
#define VERSIONUTILS_HPP

bool operator==(const Version& lhs, const Version& rhs);
bool operator!=(const Version& lhs, const Version& rhs);
bool operator< (const Version& lhs, const Version& rhs);
bool operator<=(const Version& lhs, const Version& rhs);
bool operator> (const Version& lhs, const Version& rhs);
bool operator>=(const Version& lhs, const Version& rhs);

std::ostream& operator<<(std::ostream& os, const Version& v);

std::string to_string(const Version& v);

#endif // VERSIONUTILS_HPP
