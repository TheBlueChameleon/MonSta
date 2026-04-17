#include <cstring>

#include "errorservice/catchmacros.hpp"

#include "csvservice.hpp"
#include "csvservice_dlx.hpp"

namespace CsvService
{
    // ====================================================================== //
    // helpers

    // ====================================================================== //
    // exported methods

    CsvHandle HOST_API_CALL readCsvData_dlx(const char* const filename, const ICsvService::CsvOptions csvOptions)
    {
        try {}
        CATCH_ALL_OWN(CsvHandle{nullptr})
    }

    CsvHandle HOST_API_CALL parseCsvData_dlx(const char* const rawData, const char* const origin, const ICsvService::CsvOptions csvOptions)
    {
        try {}
        CATCH_ALL_OWN(CsvHandle{nullptr})
    }

    void HOST_API_CALL freeCsvData_dlx(CsvHandle* handle)
    {
        try {}
        CATCH_ALL_OWN()
    }

    const char* HOST_API_CALL getOrigin_dlx(const CsvHandle handle)
    {
        try {}
        CATCH_ALL_OWN(nullptr)
    }

    const size_t HOST_API_CALL getRowCount_dlx(const CsvHandle handle)
    {
        try {}
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getMaxWidth_dlx(const CsvHandle handle)
    {
        try {}
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getRowWidth_dlx(const CsvHandle handle, const size_t rowIndex)
    {
        try {}
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getRowIndex_dlx(const CsvHandle handle, const char* const rowName)
    {
        try {}
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getColumnIndex_dlx(const CsvHandle handle, const char* const columnName)
    {
        try {}
        CATCH_ALL_OWN(0)
    }

    void HOST_API_CALL reIndexRows_dlx(const CsvHandle handle, const size_t columnIndex)
    {
        try {}
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL reIndexColumns_dlx(const CsvHandle handle, const size_t rowIndex)
    {
        try {}
        CATCH_ALL_OWN()
    }

    ICsvService::RowData HOST_API_CALL reserveRowBuffer_dlx(const CsvHandle handle)
    {
        const auto nullRow = ICsvService::RowData {nullptr, 0};
        try {}
        CATCH_ALL_OWN(nullRow)
    }

    void HOST_API_CALL freeRowBuffer_dlx(ICsvService::RowData* buffer)
    {
        try {}
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL getRow_dlx(const CsvHandle handle, ICsvService::RowData buffer, const size_t rowIndex)
    {
        try {}
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL getRow_dlx(const CsvHandle handle, ICsvService::RowData buffer, const char* const rowName)
    {
        try {}
        CATCH_ALL_OWN()
    }

    ICsvService::CellData HOST_API_CALL getCell_dlx(const CsvHandle handle, const size_t rowIndex, const size_t columnIndex)
    {
        const auto nullCell = ICsvService::CellData {nullptr, 0};
        try {}
        CATCH_ALL_OWN(nullCell)
    }

    ICsvService::CellData HOST_API_CALL getCell_dlx(const CsvHandle handle, const char* const rowName, const char* const columnName)
    {
        const auto nullCell = ICsvService::CellData {nullptr, 0};
        try {}
        CATCH_ALL_OWN(nullCell)
    }
}
