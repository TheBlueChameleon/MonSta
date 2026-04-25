#ifndef TEAMDEFINITIONSETUP_HPP
#define TEAMDEFINITIONSETUP_HPP

#include <filesystem>

#include <services/JsonService/IJsonService_Types.hpp>

namespace EngineBase
{
    class ErrorBuffer;
}

namespace MetaDefinition
{
    class TeamDefinition;
}

namespace SimulationMode
{

    void loadAndRegisterTeamDefinition(
        const std::filesystem::path& teamDefinitionFile,
        IJsonServiceTypes::JsonHandle& teamHandle,
        MetaDefinition::TeamDefinition& team,
        EngineBase::ErrorBuffer& eb
    );

} // namespace SimulationMode

#endif // TEAMDEFINITIONSETUP_HPP
