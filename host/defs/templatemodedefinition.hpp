#ifndef TEMPLATEMODEDEFINITION_HPP
#define TEMPLATEMODEDEFINITION_HPP

#include "basemodedefinition.hpp"

struct TemplateModeDefinition : public BaseModeDefinition
{
    TemplateModeDefinition():
        BaseModeDefinition(OperationMode::TEMPLATE, LoggingDefinition())
    {}
};

#endif // TEMPLATEMODEDEFINITION_HPP
