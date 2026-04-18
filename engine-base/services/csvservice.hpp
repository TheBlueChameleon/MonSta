#ifndef CSVSERVICE_HPP
#define CSVSERVICE_HPP

#include <string_view>

#include <services/ICsvService.hpp>

namespace CsvService
{
    ICsvService::CsvHandle HOST_API_CALL readCsvData(
        const std::string_view filename,
        const ICsvService::CsvOptions csvOptions
    );

    ICsvService::CsvHandle HOST_API_CALL parseCsvData(
        const std::string_view rawData,
        const std::string_view origin,
        const ICsvService::CsvOptions csvOptions
    );

    void HOST_API_CALL freeCsvData(ICsvService::CsvHandle* handle);

    const std::string_view HOST_API_CALL getOrigin(const ICsvService::CsvHandle handle);

    const size_t HOST_API_CALL getRowCount(const ICsvService::CsvHandle handle);
    const size_t HOST_API_CALL getMaxWidth(const ICsvService::CsvHandle handle);
    const size_t HOST_API_CALL getRowWidth(const ICsvService::CsvHandle handle, const size_t rowIndex);

    const size_t HOST_API_CALL getRowIndex(const ICsvService::CsvHandle handle, const std::string_view rowName);
    const size_t HOST_API_CALL getColumnIndex(const ICsvService::CsvHandle handle, const std::string_view columnName);

    void HOST_API_CALL reIndexRows(ICsvService::CsvHandle handle, const size_t columnIndex);
    void HOST_API_CALL reIndexColumns(ICsvService::CsvHandle handle, const size_t rowIndex);

    ICsvService::RowData HOST_API_CALL reserveRowBuffer(const ICsvService::CsvHandle handle);
    void HOST_API_CALL freeRowBuffer(ICsvService::RowData* buffer);

    void HOST_API_CALL getRow(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const size_t rowIndex);
    void HOST_API_CALL getRowByName(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const std::string_view rowName);

    ICsvService::CellData HOST_API_CALL getCell(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex);
    ICsvService::CellData HOST_API_CALL getCellByName(const ICsvService::CsvHandle handle, const std::string_view rowName, const std::string_view columnName);
}

#endif // CSVSERVICE_HPP
