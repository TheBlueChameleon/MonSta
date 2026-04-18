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

    const size_t HOST_API_CALL getRowIndex_dlx(const ICsvService::CsvHandle handle, const char* const rowName);
    const size_t HOST_API_CALL getColumnIndex_dlx(const ICsvService::CsvHandle handle, const char* const columnName);

    void HOST_API_CALL reIndexRows_dlx(ICsvService::CsvHandle handle, const size_t columnIndex);
    void HOST_API_CALL reIndexColumns_dlx(ICsvService::CsvHandle handle, const size_t rowIndex);

    ICsvService::RowData HOST_API_CALL reserveRowBuffer_dlx(const ICsvService::CsvHandle handle);
    void HOST_API_CALL freeRowBuffer_dlx(ICsvService::RowData* buffer);

    void HOST_API_CALL getRow_dlx(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const size_t rowIndex);
    void HOST_API_CALL getRowByName_dlx(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const char* const rowName);

    ICsvService::CellData HOST_API_CALL getCell_dlx(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex);
    ICsvService::CellData HOST_API_CALL getCellByName_dlx(const ICsvService::CsvHandle handle, const char* const rowName, const char* const columnName);
}

#endif // CSVSERVICE_DLX_HPP
