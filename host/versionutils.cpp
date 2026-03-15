#include <sstream>

#include <Version.hpp>

bool operator==(const Version& lhs, const Version& rhs)
{
    if (lhs.major != rhs.major)
    {
        return false;
    }
    if (lhs.minor!= rhs.minor)
    {
        return false;
    }
    if (lhs.patch != rhs.patch)
    {
        return false;
    }
    if (lhs.build != rhs.build)
    {
        return false;
    }

    return true;
}

bool operator!=(const Version& lhs, const Version& rhs)
{
    return !(lhs == rhs);
}
bool operator<(const Version& lhs, const Version& rhs)
{
    if (lhs.major < rhs.major)
    {
        return true;
    }
    else if (lhs.major > rhs.major)
    {
        return false;
    }

    if (lhs.minor < rhs.minor)
    {
        return true;
    }
    else if (lhs.minor > rhs.minor)
    {
        return false;
    }


    if (lhs.patch < rhs.patch)
    {
        return true;
    }
    else if (lhs.patch > rhs.patch)
    {
        return false;
    }

    if (lhs.build < rhs.build)
    {
        return true;
    }
    else if (lhs.build > rhs.build)
    {
        return false;
    }

    return false;
}

bool operator<=(const Version& lhs, const Version& rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

bool operator> (const Version& lhs, const Version& rhs)
{
    return !(lhs <= rhs);
}

bool operator>=(const Version& lhs, const Version& rhs)
{
    return !(lhs < rhs);
}


std::ostream& operator<<(std::ostream& os, const Version& v)
{
    return os << v.major << "." << v.minor << "." << v.patch << "." << v.build;
}


std::string to_string(const Version& v)
{
    return (std::stringstream() << v).str();
}
