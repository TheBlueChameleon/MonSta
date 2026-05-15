#include <cctype>

#include <ClientApi.hpp>

#include "stringutils.hpp"
#include "errors.hpp"

namespace EngineBase
{
    namespace detail
    {
        inline std::string_view trim(std::string_view sv)
        {
            auto is_space = [](unsigned char c)
            {
                return std::isspace(c);
            };

            while (!sv.empty() && is_space(sv.front()))
            {
                sv.remove_prefix(1);
            }

            while (!sv.empty() && is_space(sv.back()))
            {
                sv.remove_suffix(1);
            }

            return sv;
        }

        std::string_view getToken(
            std::string_view input,
            const char argsSeparator
        )
        {
            auto splitPoint = input.find(argsSeparator);
            std::string_view token = (splitPoint == std::string_view::npos)
                                     ? input
                                     : input.substr(0, splitPoint);

            input = (splitPoint == std::string_view::npos) ?
                    std::string_view{} :
                    input.substr(splitPoint + 1);

            return detail::trim(token);
        }

        std::pair<std::string_view, std::string_view> getKeyValuePair(
            std::string_view token,
            const char keyValueSeparator
        )
        {
            auto splitPoint = token.find(keyValueSeparator);
            if (splitPoint == std::string_view::npos)
            {
                // flag
                std::string key(detail::trim(token));
                if (!key.empty())
                {
                    return std::pair(key, "");
                }
            }
            else
            {
                std::string_view key   = detail::trim(token.substr(0, splitPoint));
                std::string_view value = detail::trim(token.substr(splitPoint + 1));

                if (!key.empty())
                {
                    return std::pair(key, value);
                }
            }

            return std::pair("", "");
        }
    }

    std::unordered_map<std::string, std::string> splitArgs(
        std::string_view input,
        const char argsSeparator,
        const char keyValueSeparator
    )
    {
        std::unordered_map<std::string, std::string> result;

        while (!input.empty())
        {
            std::string_view token = detail::getToken(input, argsSeparator);
            if (token.empty())
            {
                continue;
            }

            const auto kvPair = detail::getKeyValuePair(token, keyValueSeparator);
            if (!kvPair.first.empty())
            {
                result.emplace(kvPair.first.data(), kvPair.second.data());
            }
        }

        return result;
    }

    std::list<KeyValuePair> splitArgsOrdered(
        std::string_view input,
        const char argsSeparator,
        const char keyValueSeparator
    )
    {
        std::list<std::pair<std::string, std::string>> result;

        while (!input.empty())
        {
            std::string_view token = detail::getToken(input, argsSeparator);
            if (token.empty())
            {
                continue;
            }

            const auto kvPair = detail::getKeyValuePair(token, keyValueSeparator);
            if (!kvPair.first.empty())
            {
                result.emplace_back(kvPair.first.data(), kvPair.second.data());
            }
        }

        return result;
    }

}
