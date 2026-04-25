#include <format>
#include <string>

#include <runmodes/ITemplatesDefinition.hpp>

#include <services/fileservice.hpp>

#include "allowedvalueswriter.hpp"
#include "templatesmode.hpp"

namespace TemplateMode
{
    void writeAllowedValueFile()
    {
        const auto content = R"(to be done)";
        FileService::write(ALLOWED_VALUES_FILE, content);
    }

} // namespace TemplateMode
