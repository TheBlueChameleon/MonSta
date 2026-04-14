#ifndef ENTRYPOINT_TEMPLATE_HPP
#define ENTRYPOINT_TEMPLATE_HPP

#include <memory>

namespace OperationModes
{
    struct TemplateModeDefinition;
}

namespace TemplateMode
{
    void run(const OperationModes::TemplateModeDefinition& defs);
}

#endif // ENTRYPOINT_TEMPLATE_HPP
