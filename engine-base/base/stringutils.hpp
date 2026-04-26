#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <unordered_map>
#include <list>

namespace EngineBase
{
    using KeyValuePair = std::pair<std::string, std::string>;

    std::unordered_map<std::string, std::string> splitArgs(
        std::string_view input,
        const char argsSeparator = ';',
        const char keyValueSeparator = '='
    );
    std::list<KeyValuePair> splitArgsOrdered(
        std::string_view input,
        const char argsSeparator = ';',
        const char keyValueSeparator = '='
    );
}

#endif // STRINGUTILS_H
