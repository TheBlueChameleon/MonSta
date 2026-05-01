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
#include "typedefinitionsetup.hpp"

using namespace std::string_literals;
using namespace EngineBase;
using namespace Registry;
using namespace MetaDefinition;
using namespace SchemaValidation;

namespace SimulationMode
{
    // ====================================================================== //
    // helpers

    static void fetchIntoStringView(
        const std::span<ICsvService::CellData>& rowCellView,
        std::vector<std::string_view>& rowStringView
    )
    {
        const auto extract = [](const ICsvService::CellData& cell)
        {
            return cell.data;
        };

        std::transform(rowCellView.begin(), rowCellView.end(),
                       rowStringView.begin(),
                       extract
                      );
    }

    // ====================================================================== //
    // processors proper

    std::unordered_map<std::string, size_t> collectColumnIndices(
        ICsvService::CsvHandle handle,
        ErrorBuffer& eb,
        const std::filesystem::path& origin
    )
    {
        bool valid = true;
        std::unordered_map<std::string, size_t> result;

        const auto rememberColumn =[&result, &handle](const char* const columnName)
        {
            result.try_emplace(columnName, CsvService::getColumnIndex(handle, columnName));
        };

        // *INDENT-OFF*
        if (!CsvService::hasColumn(handle, TypeChart::ATTACKER)) { report(eb, "Missing column: "s + TypeChart::ATTACKER, origin); }
        if (!CsvService::hasColumn(handle, TypeChart::CATEGORY)) { report(eb, "Missing column: "s + TypeChart::CATEGORY, origin); }
        // *INDENT-ON*

        rememberColumn(TypeChart::ATTACKER);
        rememberColumn(TypeChart::CATEGORY);

        ICsvService::ColumnData typeNames = CsvService::getColumnByName(handle, TypeChart::ATTACKER);
        const auto typeNamesView = std::span(typeNames.data + 1, typeNames.data + typeNames.size);

        for (const ICsvService::CellData type : typeNamesView)
        {
            if (CsvService::hasColumn(handle, type.data))
            {
                rememberColumn(type.data);
            }
            else
            {
                valid = false;
                report(eb, "Missing column: "s + type.data, origin);
            }
        }

        if (!valid)
        {
            abort("Type chart is incomplete");
        }

        CsvService::freeColumnBuffer(typeNames);

        return result;
    }

    void transferToTypeChart(
        ICsvService::CsvHandle handle,
        const std::unordered_map<std::string, size_t>& columnIndices
    )
    {
        MemoryService::StringViewArray rowBuffer = CsvService::reserveRowBuffer(handle);
        CsvService::getRow(handle, rowBuffer.getRaw(), 0);

        auto typeDataView = std::vector<std::string_view>(rowBuffer.size() - 2);  // do not observe ATTACKER, CATEGORY

        // lookups are guaranteed to have results, or collectColumnIndices would have called abort.
        const auto typeNameColumn = columnIndices.find(TypeChart::ATTACKER)->second;
        const auto categoryColumn = columnIndices.find(TypeChart::CATEGORY)->second;

        // copy all but ATTACKER, CATEGORY into typeDataView
        const auto updateTypeDataView = [&typeDataView, &rowBuffer, &columnIndices]()
        {
            size_t i = 0;
            for (const auto& entry : columnIndices)
            {
                if (entry.first == TypeChart::ATTACKER || entry.first == TypeChart::CATEGORY)
                {
                    continue;
                }

                const auto column = entry.second;
                typeDataView[i] = rowBuffer.get(column);

                ++i;
            }
        };

        updateTypeDataView();
        typeChart.setupTypes(typeDataView);

        const size_t rowCount = CsvService::getRowCount(handle);
        for (size_t i = 1; i < rowCount; ++i)
        {
            CsvService::getRow(handle, rowBuffer.getRaw(), i);
            const auto typeName     = rowBuffer.get(typeNameColumn);
            const auto categoryName = rowBuffer.get(categoryColumn);
            const auto category = getMoveCategoryFromName(categoryName);

            updateTypeDataView();
            typeChart.setRow(typeName, category, typeDataView);
        }
    }

    void loadAndRegisterTypesDefinition(
        const std::filesystem::path& typeDefinitionFile,
        ErrorBuffer& eb
    )
    {
        try
        {
            LoggerService::traceF("  ... loading types definition from '{}'", typeDefinitionFile.c_str());

            ICsvService::CsvHandle csvHandle = CsvService::readCsvData(typeDefinitionFile, ICsvService::CsvOptions{});
            const std::unordered_map<std::string, size_t> indices = collectColumnIndices(csvHandle, eb, typeDefinitionFile);
            transferToTypeChart(csvHandle, indices);
            CsvService::freeCsvData(csvHandle);
        }
        catch (const EngineError& e)
        {
            report(eb, e.what(), typeDefinitionFile);
        }
    }

} // namespace SimulationMode
