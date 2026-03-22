#ifndef ENTRYPOINT_TEMPLATE_HPP
#define ENTRYPOINT_TEMPLATE_HPP

#include <memory>

#include "../../defs/basemodedefinition.hpp"

namespace TemplateMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // ENTRYPOINT_TEMPLATE_HPP
