#include <services/fileservice.hpp>

#include "strategyfilewriter.hpp"

namespace TemplateMode
{
    static const auto strategy = R"(to be done)";

    const std::string_view writeStrategyFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        FileService::write(defaultName, strategy);

        return defaultName;
    }

} // namespace TemplateMode
