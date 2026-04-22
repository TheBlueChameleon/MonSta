#include <algorithm>
#include <span>
#include <unordered_map>

#include <base/enginebase.hpp>

#include <services/csvservice.hpp>
#include <services/jsonservice.hpp>
#include <services/loggerservice.hpp>

#include "globals.hpp"
#include "schemavalidationconstants.hpp"

#include "simulationmode/defs/teamdefinition.hpp"
#include "simulationmode/defs/typeinfo.hpp"

#include "simulationmode/registry.hpp"
#include "simulationmode/typechart.hpp"

#include "pokemondefinitionsetup.hpp"

using namespace EngineBase;
using namespace SchemaValidation;
using namespace std::string_literals;

namespace SimulationMode
{
    std::unordered_map<std::string, size_t> assertPokemonDatabaseDataComplete(
        const std::filesystem::__cxx11::path& pokemonDefinitionFile,
        ICsvService::CsvHandle                handle,
        ICsvService::RowData                  rowBuffer,
        EngineBase::ErrorBuffer&              eb
    )
    {
        bool resultValid = true;
        std::unordered_map<std::string, size_t> result;
        CsvService::getRow(handle, rowBuffer, 0);
        std::span<ICsvService::CellData> rowView(
            rowBuffer.data,
            rowBuffer.data + rowBuffer.size
        );

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
            const auto equals = [searchTerm](const ICsvService::CellData cell)
            {
                return searchTerm == cell.data;
            };

            auto it = std::find_if(rowView.begin(), rowView.end(), equals);
            auto id = std::distance(rowView.begin(), it);

            if (it == rowView.end())
            {
                eb.append(ApiStatusCode::INVALID_USER_INPUT,
                          "In pokemon definition file '"s + pokemonDefinitionFile.c_str() + "': "
                          "Missing Column header '" +  searchTerm.data() + "'"
                         );
                resultValid = false;
            }
            else
            {
                result.try_emplace(searchTerm.data(), id);
            }
        }

        if (!resultValid)
        {
            result.clear();
        }
        return result;
    }

    void transferToPokemonDatabase(
        const std::filesystem::__cxx11::path&         pokemonDefinitionFile,
        ICsvService::CsvHandle                        handle,
        ICsvService::RowData                          rowBuffer,
        const std::unordered_map<std::string, size_t> columnNames,
        EngineBase::ErrorBuffer&                      eb
    )
    {
        const size_t rowCount = CsvService::getRowCount(handle);
        std::string_view field;

        const auto extractStringAndRememberField = [&field, &columnNames](
                                                       const std::string_view fieldName,
                                                       const ICsvService::RowData rowBuffer
                                                   )
        {
            field = fieldName;
            const auto it = columnNames.find(fieldName.data());
            const size_t column = it->second;
            const ICsvService::CellData cell = rowBuffer.data[column];
            return cell.data;
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
                const std::string secondary = extractStringAndRememberField(PokemonDatabase::TYPE2, rowBuffer);
                if (!secondary.empty())
                {
                    entry.type.secondary = secondary;
                }

                pokemonDatabase.addSpecies(species, entry);

            }
            catch (const EngineError& e)
            {
                eb.append(e);
            }
            catch (const std::invalid_argument&)
            {
                eb.append(ApiStatusCode::INVALID_USER_INPUT,
                          "In pokemon definition file '"s + pokemonDefinitionFile.c_str() + "': "
                          "Invalid Argument in line "s + std::to_string(row + 1) + " "
                          "in field '" + field.data() + "'"
                         );
            }
            catch (const std::out_of_range&)
            {
                eb.append(ApiStatusCode::INVALID_USER_INPUT,
                          "In pokemon definition file '"s + pokemonDefinitionFile.c_str() + "': "
                          "Invalid Argument in line "s + std::to_string(row + 1) + " "
                          "in field '" + field.data() + "'"
                         );
            }
        }
    }

    void loadAndRegisterPokemon(const std::filesystem::__cxx11::path& pokemonDefinitionFile, EngineBase::ErrorBuffer& eb)
    {
        try
        {
            LoggerService::traceF("  ... loading pokemon definition from '{}'", pokemonDefinitionFile.c_str());

            ICsvService::CsvHandle csvHandle = CsvService::readCsvData(pokemonDefinitionFile, ICsvService::CsvOptions{});
            ICsvService::RowData   rowBuffer = CsvService::reserveRowBuffer(csvHandle);

            const std::unordered_map<std::string, size_t> columnNames =
                assertPokemonDatabaseDataComplete(
                    pokemonDefinitionFile,
                    csvHandle,
                    rowBuffer,
                    eb
                );
            if (!columnNames.empty())
            {
                transferToPokemonDatabase(
                    pokemonDefinitionFile,
                    csvHandle,
                    rowBuffer,
                    columnNames,
                    eb
                );
            }

            CsvService::freeRowBuffer(rowBuffer);
            CsvService::freeCsvData(csvHandle);
        }
        catch (const EngineError& e)
        {
            eb.append(e);
        }
    }

} // namespace SimulationMode
