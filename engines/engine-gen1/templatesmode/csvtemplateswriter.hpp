#ifndef CSVTEMPLATESWRITER_HPP
#define CSVTEMPLATESWRITER_HPP

#include <string_view>

namespace TemplateMode
{
    const std::string_view writePkmnDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    );

    const std::string_view writeMoveDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    );

    const std::string_view writeTypeDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    );

    const std::string_view writeItemDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    );

} // namespace TemplateMode

#endif // CSVTEMPLATESWRITER_HPP
