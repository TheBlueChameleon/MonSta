#ifndef CSVSERVICE_DLX_HPP
#define CSVSERVICE_DLX_HPP

#include <CallingConventions.hpp>

#include <services/ICsvService.hpp>

namespace CsvService
{
    ICsvService::CsvHandle HOST_API_CALL readCsvData_dlx(
        const char* const filename,
        const ICsvService::CsvOptions csvOptions
    );

    ICsvService::CsvHandle HOST_API_CALL parseCsvData_dlx(
        const char* const rawData,
        const char* const origin,
        const ICsvService::CsvOptions csvOptions
    );

    void HOST_API_CALL freeCsvData_dlx(ICsvService::CsvHandle* handle);

    const char* HOST_API_CALL getOrigin_dlx(const ICsvService::CsvHandle handle);

    const size_t HOST_API_CALL getRowCount_dlx(const ICsvService::CsvHandle handle);
    const size_t HOST_API_CALL getMaxWidth_dlx(const ICsvService::CsvHandle handle);
    const size_t HOST_API_CALL getRowWidth_dlx(const ICsvService::CsvHandle handle, const size_t rowIndex);

    const bool   HOST_API_CALL hasRow_dlx(const ICsvService::CsvHandle handle, const char* const rowName);
    const bool   HOST_API_CALL hasColumn_dlx(const ICsvService::CsvHandle handle, const char* const columnName);
    const size_t HOST_API_CALL getRowIndex_dlx(const ICsvService::CsvHandle handle, const char* const rowName);
    const size_t HOST_API_CALL getColumnIndex_dlx(const ICsvService::CsvHandle handle, const char* const columnName);

    void HOST_API_CALL reIndexRows_dlx(ICsvService::CsvHandle handle, const size_t columnIndex);
    void HOST_API_CALL reIndexColumns_dlx(ICsvService::CsvHandle handle, const size_t rowIndex);

    IMemoryService::StringViewArray HOST_API_CALL reserveRowBuffer_dlx(const ICsvService::CsvHandle handle);
    void HOST_API_CALL freeRowBuffer_dlx(ICsvService::RowData* buffer);

    void HOST_API_CALL getRow_dlx(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const size_t rowIndex);
    void HOST_API_CALL getRowByName_dlx(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const char* const rowName);

    ICsvService::ColumnData HOST_API_CALL getColumn_dlx(const ICsvService::CsvHandle handle, const size_t columnIndex);
    ICsvService::ColumnData HOST_API_CALL getColumnByName_dlx(const ICsvService::CsvHandle handle, const char* const columnName);
    void HOST_API_CALL freeColumnBuffer_dlx(ICsvService::ColumnData* columnData);

    IMemoryService::StringView HOST_API_CALL getCell_dlx(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex);
    IMemoryService::StringView HOST_API_CALL getCellByName_dlx(const ICsvService::CsvHandle handle, const char* const rowName, const char* const columnName);
}

#endif // CSVSERVICE_DLX_HPP
