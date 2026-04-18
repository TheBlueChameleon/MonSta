#include "csvservice.hpp"
#include "services.hpp"

using namespace Services;

namespace CsvService
{
    ICsvService::CsvHandle readCsvData(const std::string_view filename, const ICsvService::CsvOptions csvOptions)
    {
        auto result = csvService().readCsvData(filename.data(), csvOptions);
        rethrowHostError();
        return result;
    }

    ICsvService::CsvHandle parseCsvData(
        const std::string_view rawData,
        const std::string_view origin,
        const ICsvService::CsvOptions csvOptions
    )
    {
        auto result = csvService().parseCsvData(rawData.data(), origin.data(), csvOptions);
        rethrowHostError();
        return result;
    }

    void freeCsvData(ICsvService::CsvHandle* handle)
    {
        csvService().freeCsvData(handle);
        rethrowHostError();
    }

    const std::string_view getOrigin(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().getOrigin(handle);
        rethrowHostError();
        return result;
    }

    const size_t getRowCount(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().getRowCount(handle);
        rethrowHostError();
        return result;
    }

    const size_t getMaxWidth(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().getMaxWidth(handle);
        rethrowHostError();
        return result;
    }

    const size_t getRowWidth(const ICsvService::CsvHandle handle, const size_t rowIndex)
    {
        auto result = csvService().getRowWidth(handle, rowIndex);
        rethrowHostError();
        return result;
    }

    const size_t getRowIndex(const ICsvService::CsvHandle handle, const std::string_view rowName)
    {
        auto result = csvService().getRowIndex(handle, rowName.data());
        rethrowHostError();
        return result;
    }

    const size_t getColumnIndex(const ICsvService::CsvHandle handle, const std::string_view columnName)
    {
        auto result = csvService().getColumnIndex(handle, columnName.data());
        rethrowHostError();
        return result;
    }

    void reIndexRows(ICsvService::CsvHandle handle, const size_t columnIndex)
    {
        csvService().reIndexRows(handle, columnIndex);
        rethrowHostError();
    }

    void reIndexColumns(ICsvService::CsvHandle handle, const size_t rowIndex)
    {
        csvService().reIndexColumns(handle, rowIndex);
        rethrowHostError();
    }

    ICsvService::RowData reserveRowBuffer(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().reserveRowBuffer(handle);
        rethrowHostError();
        return result;
    }

    void freeRowBuffer(ICsvService::RowData* buffer)
    {
        csvService().freeRowBuffer(buffer);
        rethrowHostError();
    }

    void getRow(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const size_t rowIndex)
    {
        csvService().getRow(handle, buffer, rowIndex);
        rethrowHostError();
    }

    void getRowByName(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const std::string_view rowName)
    {
        csvService().getRowByName(handle, buffer, rowName.data());
        rethrowHostError();
    }

    ICsvService::CellData getCell(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex)
    {
        auto result = csvService().getCell(handle, rowIndex, columnIndex);
        rethrowHostError();
        return result;
    }

    ICsvService::CellData getCellByName(
        const ICsvService::CsvHandle handle,
        const std::string_view rowName,
        const std::string_view columnName
    )
    {
        auto result = csvService().getCellByName(handle, rowName.data(), columnName.data());
        rethrowHostError();
        return result;
    }
}
