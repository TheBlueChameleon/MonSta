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

#include "typedefinitionsetup.hpp"

using namespace EngineBase;
using namespace SchemaValidation;
using namespace std::string_literals;

namespace SimulationMode
{
    // ====================================================================== //
    // helpers

    [[noreturn]] static void abort(
        const std::string_view message,
        const std::filesystem::path& origin
    )
    {
        throw EngineError(
            ApiStatusCode::INVALID_USER_INPUT,
            "In team definition file '"s + origin.c_str() + "' " + message.data()
        );
    }

    static void report(
        ErrorBuffer& eb,
        const std::string_view message,
        const std::filesystem::path& origin
    )
    {
        eb.append(
            ApiStatusCode::INVALID_USER_INPUT,
            "In team definition file '"s + origin.c_str() + "' " + message.data()
        );
    }

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

    static const char* const getRowItem(
        const ICsvService::RowData& rowBuffer,
        size_t index
    )
    {
        return rowBuffer.data[index].data;
    }

    // ====================================================================== //
    // processors proper

    void assertTypeChartDataComplete(
        ICsvService::CsvHandle handle,
        ErrorBuffer& eb,
        const std::filesystem::path& origin
    )
    {
        bool valid = true;
        // *INDENT-OFF*
        if (!CsvService::hasColumn(handle, TypeChart::ATTACKER)) { report(eb, "Missing column: "s + TypeChart::ATTACKER, origin); }
        if (!CsvService::hasColumn(handle, TypeChart::CATEGORY)) { report(eb, "Missing column: "s + TypeChart::CATEGORY, origin); }
        // *INDENT-ON*

        ICsvService::ColumnData typeNames = CsvService::getColumnByName(handle, TypeChart::ATTACKER);
        const auto typeNamesView = std::span(typeNames.data + 1, typeNames.data + typeNames.size);

        for (const ICsvService::CellData type : typeNamesView)
        {
            if (!CsvService::hasColumn(handle, type.data))
            {
                valid = false;
                report(eb, "Missing column: "s + type.data, origin);
            }
        }

        if (!valid)
        {
            abort("Type chart is incomplete", origin);
        }

        CsvService::freeColumnBuffer(typeNames);
    }

    void transferToTypeChart(ICsvService::CsvHandle handle)
    {
        const size_t rowCount = CsvService::getRowCount(handle);
        ICsvService::RowData rowBuffer = CsvService::reserveRowBuffer(handle);
        CsvService::getRow(handle, rowBuffer, 0);

        auto rowCellView = std::span<ICsvService::CellData>(
                               rowBuffer.data + 2,              // skip the "Attacker" and "Category" entries
                               rowBuffer.data + rowBuffer.size
                           );
        auto rowStringView = std::vector<std::string_view>(rowCellView.size());
        fetchIntoStringView(rowCellView, rowStringView);
        typeChart.setupTypes(rowStringView);

        for (size_t i = 1; i < rowCount; ++i)
        {
            CsvService::getRow(handle, rowBuffer, i);           // also updates rowCellView
            const auto rowName = getRowItem(rowBuffer, 0);
            const auto categoryName = getRowItem(rowBuffer, 1);
            const auto category = getMoveCategoryFromName(categoryName);
            fetchIntoStringView(rowCellView, rowStringView);
            typeChart.setRow(rowName, category, rowStringView);
        }

        CsvService::freeRowBuffer(rowBuffer);
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
            assertTypeChartDataComplete(csvHandle, eb, typeDefinitionFile);
            transferToTypeChart(csvHandle);
            CsvService::freeCsvData(csvHandle);
        }
        catch (const EngineError& e)
        {
            eb.append(e);
        }
    }
} // namespace SimulationMode
