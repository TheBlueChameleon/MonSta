#include <algorithm>
#include <span>
#include <unordered_map>

#include <base/errorbuffer.hpp>

#include <services/csvservice.hpp>
#include <services/jsonservice.hpp>
#include <services/loggerservice.hpp>

#include "shared/schemavalidationconstants.hpp"

#include "shared/defs/teamdefinition.hpp"
#include "shared/defs/typeinfo.hpp"

#include "shared/registry/registry.hpp"
#include "shared/registry/typechart.hpp"

#include "setuperrorhandling.hpp"

using namespace EngineBase;
using namespace MetaDefinition;
using namespace Registry;
using namespace SchemaValidation;
using namespace std::string_literals;

namespace SimulationMode
{
    static std::unordered_map<std::string, size_t> collectColumnIndices(
        ICsvService::CsvHandle          handle,
        const std::filesystem::path&    pokemonDefinitionFile,
        EngineBase::ErrorBuffer&        eb
    )
    {
        bool resultValid = true;
        std::unordered_map<std::string, size_t> result;

        for (const std::string_view searchTerm :
             {
                 PokemonDatabase::SPECIES,
                 PokemonDatabase::HP,
                 PokemonDatabase::ATK,
                 PokemonDatabase::DEF,
                 PokemonDatabase::SPC,
                 PokemonDatabase::SPD,
                 PokemonDatabase::TYPE1,
                 PokemonDatabase::TYPE2,
                 PokemonDatabase::EXPYIELD,
                 PokemonDatabase::EXPGROUP
             })
        {
            if (CsvService::hasColumn(handle, searchTerm))
            {
                const auto id = CsvService::getColumnIndex(handle, searchTerm);
                result.try_emplace(searchTerm.data(), id);
            }
            else
            {
                report(eb, "Missing Column header '"s +  searchTerm.data() + "'", pokemonDefinitionFile);
                resultValid = false;
            }
        }

        if (!resultValid)
        {
            result.clear();
        }

        return result;
    }

    static void transferToPokemonDatabase(
        ICsvService::CsvHandle                          handle,
        const std::unordered_map<std::string, size_t>&  columnNames,
        const std::filesystem::path&                    pokemonDefinitionFile,
        EngineBase::ErrorBuffer&                        eb
    )
    {
        const size_t rowCount = CsvService::getRowCount(handle);
        MemoryService::StringViewArray rowBuffer = CsvService::reserveRowBuffer(handle);
        std::string_view field;

        const auto extractStringAndRememberField = [&field, &columnNames](
                                                       const std::string_view fieldName,
                                                       const MemoryService::StringViewArray& rowBuffer
                                                   )
        {
            field = fieldName;
            const auto it = columnNames.find(fieldName.data());
            const size_t column = it->second;
            return rowBuffer.get(column).data();
        };

        for (size_t row = 1; row < rowCount; ++row)
        {
            try
            {
                CsvService::getRow(handle, rowBuffer, row);

                const std::string species = extractStringAndRememberField(PokemonDatabase::SPECIES, rowBuffer);
                PokemonDatabaseEntry entry;

                entry.HP       =                  std::stoi(extractStringAndRememberField(PokemonDatabase::HP,       rowBuffer));
                entry.ATK      =                  std::stoi(extractStringAndRememberField(PokemonDatabase::ATK,      rowBuffer));
                entry.DEF      =                  std::stoi(extractStringAndRememberField(PokemonDatabase::DEF,      rowBuffer));
                entry.SPC      =                  std::stoi(extractStringAndRememberField(PokemonDatabase::SPC,      rowBuffer));
                entry.SPD      =                  std::stoi(extractStringAndRememberField(PokemonDatabase::SPD,      rowBuffer));
                entry.expYield =                  std::stoi(extractStringAndRememberField(PokemonDatabase::EXPYIELD, rowBuffer));
                entry.expGroup = getExperienceGroupFromName(extractStringAndRememberField(PokemonDatabase::EXPGROUP, rowBuffer));

                entry.type.primary =  extractStringAndRememberField(PokemonDatabase::TYPE1, rowBuffer);
                const std::string_view secondary = extractStringAndRememberField(PokemonDatabase::TYPE2, rowBuffer);
                if (!secondary.empty())
                {
                    entry.type.secondary = secondary;
                }
                entry.typeID = entry.type.toTypeID();

                pokemonDatabase.addSpecies(species, entry);
            }
            catch (const EngineError& e)
            {
                report(eb,
                       e.what(),
                       pokemonDefinitionFile
                      );
            }
            catch (const std::invalid_argument&)
            {
                report(eb,
                       "Invalid Argument in line "s + std::to_string(row + 1) + " in field '" + field.data() + "'",
                       pokemonDefinitionFile
                      );
            }
            catch (const std::out_of_range&)
            {
                report(eb,
                       "Invalid Argument in line "s + std::to_string(row + 1) + " in field '" + field.data() + "'",
                       pokemonDefinitionFile
                      );
            }
        }
    }

    void loadAndRegisterPokemon(const std::filesystem::path& pokemonDefinitionFile, EngineBase::ErrorBuffer& eb)
    {
        try
        {
            LoggerService::traceF("  ... loading pokemon definition from '{}'", pokemonDefinitionFile.c_str());

            ICsvService::CsvHandle csvHandle = CsvService::readCsvData(pokemonDefinitionFile, ICsvService::CsvOptions{});

            const std::unordered_map<std::string, size_t> columnNames = collectColumnIndices(csvHandle, pokemonDefinitionFile, eb);
            if (!columnNames.empty())
            {
                transferToPokemonDatabase(
                    csvHandle,
                    columnNames,
                    pokemonDefinitionFile,
                    eb
                );
            }

            CsvService::freeCsvData(csvHandle);
        }
        catch (const EngineError& e)
        {
            report(eb, e.what(), pokemonDefinitionFile);
        }

    }

} // namespace SimulationMode
