#ifndef TYPEDEFINITIONSETUP_HPP
#define TYPEDEFINITIONSETUP_HPP

#include <filesystem>

namespace EngineBase
{
    class ErrorBuffer;
}

namespace SimulationMode
{
    void loadAndRegisterTypesDefinition(
        const std::filesystem::path& typeDefinitionFile,
        EngineBase::ErrorBuffer& eb
    );

} // namespace SimulationMode

#endif // TYPEDEFINITIONSETUP_HPP
