#include <format>
#include <string>

#include <runmodes/ITemplatesDefinition.hpp>

#include <services/fileservice.hpp>
#include <services/jsonservice.hpp>
#include <services/loggerservice.hpp>

#include "csvtemplateswriter.hpp"

namespace TemplateMode
{
    const std::string_view writePkmnDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";

        FileService::write(defaultName, content);

        return defaultName;
    }

    const std::string_view writeMoveDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";
        FileService::write(defaultName, content);

        return defaultName;
    }

    const std::string_view writeTypeDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";
        FileService::write(defaultName, content);

        return defaultName;
    }

    const std::string_view writeItemDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";
        FileService::write(defaultName, content);

        return defaultName;
    }

} // namespace TemplateMode
