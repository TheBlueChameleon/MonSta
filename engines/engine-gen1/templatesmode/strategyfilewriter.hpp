#ifndef STRATEGYFILEWRITER_HPP
#define STRATEGYFILEWRITER_HPP

#include <string_view>

namespace TemplateMode
{
    const std::string_view writeStrategyFile(
        const std::string_view inputName,
        const std::string_view defaultName
    );

} // namespace TemplateMode

#endif // STRATEGYFILEWRITER_HPP
