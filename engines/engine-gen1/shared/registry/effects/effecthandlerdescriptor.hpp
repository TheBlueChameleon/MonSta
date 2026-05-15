#ifndef EFFECTHANDLERDESCRIPTOR_HPP
#define EFFECTHANDLERDESCRIPTOR_HPP

#include <functional>
#include <string>

namespace MetaDefinition
{
    class EffectHandler;
    struct EffectHandlerDescriptor
    {
        std::string effectName;
        std::string effectHelpText;
        std::function<EffectHandler(const std::string_view)> effectBuilder;
    };
}
#endif // EFFECTHANDLERDESCRIPTOR_HPP
