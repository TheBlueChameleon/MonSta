#ifndef ICSVSERVICE_HPP
#define ICSVSERVICE_HPP

#include <cstddef>

#include <CallingConventions.hpp>

struct ICsvService
{
    struct CsvOptions
    {
        char delimiter = ',';
        char quoteChar = '"';
        char commentChar = '#';
        size_t headerRow =  0;
        size_t keyColumn = -1u;
    };

    struct CsvHandle
    {
        void* data;
    };

    struct CellData
    {
        const char* data;
        size_t      size;
    };

    struct RowData
    {
        CellData* data;
        size_t    size;
    };

    struct ColumnData
    {
        CellData* data;
        size_t    size;
    };

    ICsvService::CsvHandle(*const HOST_API_CALL readCsvData)(
        const char* const filename,
        const ICsvService::CsvOptions csvOptions
    );

    ICsvService::CsvHandle(*const HOST_API_CALL parseCsvData)(
        const char* const rawData,
        const char* const origin,
        const ICsvService::CsvOptions csvOptions
    );

    void HOST_API_CALL(*const freeCsvData)(ICsvService::CsvHandle* handle);

    const char* (*const HOST_API_CALL getOrigin)(const ICsvService::CsvHandle handle);

    const size_t (*const HOST_API_CALL getRowCount)(const ICsvService::CsvHandle handle);
    const size_t (*const HOST_API_CALL getMaxWidth)(const ICsvService::CsvHandle handle);
    const size_t (*const HOST_API_CALL getRowWidth)(const ICsvService::CsvHandle handle, const size_t rowIndex);

    const bool (*const HOST_API_CALL hasRow)(const ICsvService::CsvHandle handle, const char* const rowName);
    const bool (*const HOST_API_CALL hasColumn)(const ICsvService::CsvHandle handle, const char* const columnName);
    const size_t (*const HOST_API_CALL getRowIndex)(const ICsvService::CsvHandle handle, const char* const rowName);
    const size_t (*const HOST_API_CALL getColumnIndex)(const ICsvService::CsvHandle handle, const char* const columnName);

    void HOST_API_CALL(*const reIndexRows)(ICsvService::CsvHandle handle, const size_t columnIndex);
    void HOST_API_CALL(*const reIndexColumns)(ICsvService::CsvHandle handle, const size_t rowIndex);

    ICsvService::RowData HOST_API_CALL(*const reserveRowBuffer)(const ICsvService::CsvHandle handle);
    void HOST_API_CALL(*const freeRowBuffer)(ICsvService::RowData* buffer);

    void HOST_API_CALL(*const getRow)(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const size_t rowIndex);
    void HOST_API_CALL(*const getRowByName)(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const char* const rowName);

    ICsvService::ColumnData(*const HOST_API_CALL getColumn)(const ICsvService::CsvHandle handle, const size_t columnIndex);
    ICsvService::ColumnData(*const HOST_API_CALL getColumnByName)(const ICsvService::CsvHandle handle, const char* const columnName);
    void (*const HOST_API_CALL freeColumnBuffer)(ICsvService::ColumnData* columnData);

    ICsvService::CellData HOST_API_CALL(*const getCell)(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex);
    ICsvService::CellData HOST_API_CALL(*const getCellByName)(const ICsvService::CsvHandle handle, const char* const rowName, const char* const columnName);
};

#endif // ICSVSERVICE_HPP
