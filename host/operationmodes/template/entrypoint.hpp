#ifndef ENTRYPOINT_TEMPLATE_HPP
#define ENTRYPOINT_TEMPLATE_HPP

#include <memory>

struct BaseModeDefinition;

namespace TemplateMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // ENTRYPOINT_TEMPLATE_HPP
