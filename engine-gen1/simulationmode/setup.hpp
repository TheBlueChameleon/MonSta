#ifndef SETUP_HPP
#define SETUP_HPP

#include <filesystem>

namespace EngineBase
{
    class ErrorBuffer;
}

namespace SimulationMode
{
    void loadAndRegisterPokemon(
        const std::filesystem::path& pokemonDefinitionFile,
        EngineBase::ErrorBuffer& eb
    );
} // namespace SimulationMode

#endif // SETUP_HPP
