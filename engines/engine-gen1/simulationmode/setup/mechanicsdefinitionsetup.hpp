#ifndef MECHANICSDEFINITIONSETUP_HPP
#define MECHANICSDEFINITIONSETUP_HPP

#include <filesystem>

namespace EngineBase
{
    class ErrorBuffer;
}

namespace SimulationMode
{
    void loadAndRegisterMechanicsDefinition(
        const std::filesystem::path& mechanicsDefinitionFile,
        EngineBase::ErrorBuffer& eb
    );
} // namespace SimulationMode

#endif // MECHANICSDEFINITIONSETUP_HPP
