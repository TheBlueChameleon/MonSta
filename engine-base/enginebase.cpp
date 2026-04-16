#include <cctype>

#include <ClientApi.hpp>

#include "services/errorservice.hpp"

#include "enginebase.hpp"
#include "errors.hpp"

namespace EngineBase
{
    void handleException(const EngineError& e)
    {
        ErrorService::setError(e.getErrorCode(), e.what());
        ErrorService::terminateAbnormally();
    }

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
    }

    std::unordered_map<std::string, std::string> splitArgs(std::string_view input)
    {
        std::unordered_map<std::string, std::string> result;

        while (!input.empty())
        {
            // split at ';'
            auto pos = input.find(';');
            std::string_view token = (pos == std::string_view::npos)
                                     ? input
                                     : input.substr(0, pos);

            input = (pos == std::string_view::npos)
                    ? std::string_view{}
                    :
                    input.substr(pos + 1);

            token = detail::trim(token);
            if (token.empty())
            {
                continue;
            }

            // check for key=value
            auto eq = token.find('=');
            if (eq == std::string_view::npos)
            {
                // flag
                std::string key(detail::trim(token));
                if (!key.empty())
                {
                    result.emplace(std::move(key), "true");
                }
            }
            else
            {
                std::string_view key_sv = detail::trim(token.substr(0, eq));
                std::string_view val_sv = detail::trim(token.substr(eq + 1));

                if (!key_sv.empty())
                {
                    result.emplace(std::string(key_sv), std::string(val_sv));
                }
            }
        }

        return result;
    }
}
