#ifndef EFFECTHANDLERDESCRIPTOR_H
#define EFFECTHANDLERDESCRIPTOR_H

#include <functional>
#include <string>

namespace MetaDefinition
{
    class EffectHandler;
    struct EffectHandlerDescriptor
    {
        std::string effectName;
        std::string effectHelpText;
        std::function<EffectHandler&(const std::string_view)> effectBuilder;
    };
}
#endif // EFFECTHANDLERDESCRIPTOR_H
