#ifndef JSONTEMPLATESWRITER_HPP
#define JSONTEMPLATESWRITER_HPP

#include <string_view>

namespace TemplateMode
{
    const std::string_view writeMechanicsDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    );

    const std::string_view writeTeamDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName,
        const std::string_view playerType
    );

    void writeSchemas();

} // namespace TemplateMode

#endif // JSONTEMPLATESWRITER_HPP
