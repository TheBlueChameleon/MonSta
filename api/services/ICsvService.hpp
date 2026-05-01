#ifndef ICSVSERVICE_HPP
#define ICSVSERVICE_HPP

#include <cstddef>

#include <CallingConventions.hpp>

#include <services/IMemoryService.hpp>

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

    // ====================================================================== //
    // legacy

    struct CellData
    {
        const char* data;
        size_t      size;
    };

    struct ColumnData
    {
        CellData* data;
        size_t    size;
    };

    // EOF legacy
    // ====================================================================== //

    ICsvService::CsvHandle(HOST_API_CALL* const readCsvData)(
        const char* const filename,
        const ICsvService::CsvOptions csvOptions
    );

    ICsvService::CsvHandle(HOST_API_CALL* const parseCsvData)(
        const char* const rawData,
        const char* const origin,
        const ICsvService::CsvOptions csvOptions
    );

    void (HOST_API_CALL* const freeCsvData)(ICsvService::CsvHandle* handle);

    const char* (HOST_API_CALL* const getOrigin)(const ICsvService::CsvHandle handle);

    const size_t (HOST_API_CALL* const getRowCount)(const ICsvService::CsvHandle handle);
    const size_t (HOST_API_CALL* const getMaxWidth)(const ICsvService::CsvHandle handle);
    const size_t (HOST_API_CALL* const getRowWidth)(const ICsvService::CsvHandle handle, const size_t rowIndex);

    const bool (HOST_API_CALL* const hasRow)(const ICsvService::CsvHandle handle, const char* const rowName);
    const bool (HOST_API_CALL* const hasColumn)(const ICsvService::CsvHandle handle, const char* const columnName);
    const size_t (HOST_API_CALL* const getRowIndex)(const ICsvService::CsvHandle handle, const char* const rowName);
    const size_t (HOST_API_CALL* const getColumnIndex)(const ICsvService::CsvHandle handle, const char* const columnName);

    void (HOST_API_CALL* const reIndexRows)(ICsvService::CsvHandle handle, const size_t columnIndex);
    void (HOST_API_CALL* const reIndexColumns)(ICsvService::CsvHandle handle, const size_t rowIndex);

    IMemoryService::StringViewArray(HOST_API_CALL* const reserveRowBuffer)(const ICsvService::CsvHandle handle);
    void (HOST_API_CALL* const getRow)(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const size_t rowIndex);
    void (HOST_API_CALL* const getRowByName)(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const char* const rowName);

    ICsvService::ColumnData(HOST_API_CALL* const getColumn)(const ICsvService::CsvHandle handle, const size_t columnIndex);
    ICsvService::ColumnData(HOST_API_CALL* const getColumnByName)(const ICsvService::CsvHandle handle, const char* const columnName);
    // TODO: remove
    void (HOST_API_CALL* const freeColumnBuffer)(ICsvService::ColumnData* columnData);
    // EOF: remove

    IMemoryService::StringView(HOST_API_CALL* const getCell)(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex);
    IMemoryService::StringView(HOST_API_CALL* const getCellByName)(const ICsvService::CsvHandle handle, const char* const rowName, const char* const columnName);
};

#endif // ICSVSERVICE_HPP
