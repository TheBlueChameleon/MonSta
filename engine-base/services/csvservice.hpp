#ifndef CSVSERVICE_HPP
#define CSVSERVICE_HPP

#include <filesystem>
#include <string_view>

#include <services/ICsvService.hpp>

namespace CsvService
{
    ICsvService::CsvHandle readCsvData(
        const std::filesystem::path& filename,
        const ICsvService::CsvOptions csvOptions
    );

    ICsvService::CsvHandle parseCsvData(
        const std::string_view rawData,
        const std::string_view origin,
        const ICsvService::CsvOptions csvOptions
    );

    void freeCsvData(ICsvService::CsvHandle& handle);

    const std::string_view getOrigin(const ICsvService::CsvHandle handle);

    const size_t getRowCount(const ICsvService::CsvHandle handle);
    const size_t getMaxWidth(const ICsvService::CsvHandle handle);
    const size_t getRowWidth(const ICsvService::CsvHandle handle, const size_t rowIndex);

    const bool hasRow(const ICsvService::CsvHandle handle, const std::string_view rowName);
    const bool hasColumn(const ICsvService::CsvHandle handle, const std::string_view columnName);
    const size_t getRowIndex(const ICsvService::CsvHandle handle, const std::string_view rowName);
    const size_t getColumnIndex(const ICsvService::CsvHandle handle, const std::string_view columnName);

    void reIndexRows(ICsvService::CsvHandle handle, const size_t columnIndex);
    void reIndexColumns(ICsvService::CsvHandle handle, const size_t rowIndex);

    IMemoryService::StringViewArray reserveRowBuffer(const ICsvService::CsvHandle handle);
    void freeRowBuffer(ICsvService::RowData& buffer);

    void getRow(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const size_t rowIndex);
    void getRowByName(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const std::string_view rowName);

    ICsvService::ColumnData getColumn(const ICsvService::CsvHandle handle, const size_t columnIndex);
    ICsvService::ColumnData getColumnByName(const ICsvService::CsvHandle handle, const std::string_view columnName);
    void freeColumnBuffer(ICsvService::ColumnData& columnData);

    IMemoryService::StringView getCell(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex);
    IMemoryService::StringView getCellByName(const ICsvService::CsvHandle handle, const std::string_view rowName, const std::string_view columnName);
}

#endif // CSVSERVICE_HPP
