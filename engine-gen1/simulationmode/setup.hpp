#ifndef SETUP_HPP
#define SETUP_HPP

#include <filesystem>

#include <services/JsonService/IJsonService_Types.hpp>

namespace EngineBase
{
    class ErrorBuffer;
}

namespace SimulationMode
{
    class TeamDefinition;

    void loadAndRegisterMechanicsDefinition(
        const std::filesystem::path& mechanicsDefinitionFile,
        EngineBase::ErrorBuffer& eb
    );

    void loadAndRegisterTeamDefinition(
        const std::filesystem::path& teamDefinitionFile,
        IJsonServiceTypes::JsonHandle& teamHandle,
        TeamDefinition& team,
        EngineBase::ErrorBuffer& eb
    );

    void loadAndRegisterTypesDefinition(
        const std::filesystem::path& typeDefinitionFile,
        EngineBase::ErrorBuffer& eb
    );
} // namespace SimulationMode

#endif // SETUP_HPP
