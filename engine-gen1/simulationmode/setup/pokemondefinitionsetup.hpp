#ifndef POKEMONDEFINITIONSETUP_H
#define POKEMONDEFINITIONSETUP_H

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

#endif // POKEMONDEFINITIONSETUP_H
