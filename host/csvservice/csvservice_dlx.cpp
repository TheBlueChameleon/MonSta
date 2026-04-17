#include <algorithm>
#include <cstring>
#include <string>

#include "errorservice/catchmacros.hpp"

#include "csvservice.hpp"
#include "csvservice_dlx.hpp"

using namespace std::string_literals;

namespace CsvService
{
    // ====================================================================== //
    // helpers

    static void assertSanePointer(const void* const ptr)
    {
        if (ptr == nullptr)
        {
            throw InvalidUserInput("Attempted to process null pointer");
        }
    }

    static void assertSaneString(const char* const string)
    {
        if (string == nullptr)
        {
            throw InvalidUserInput("Attempted to process null string");
        }
    }

    static void assertSaneHandle(const CsvHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw InvalidUserInput("Attempted to process null CSV handle");
        }
    }

    static const IndexedCsvData& toCsvData(const CsvHandle handle)
    {
        return *static_cast<const IndexedCsvData*>(handle.data);
    }

    static IndexedCsvData& toCsvDataMutable(CsvHandle handle)
    {
        return *static_cast<IndexedCsvData*>(handle.data);
    }

    static void transformRowToCData(
        const std::vector<std::string>& row,
        ICsvService::RowData buffer
    )
    {
        std::transform(row.begin(), row.end(),
                       buffer.data,
                       [](const std::string& cell)
        {
            return ICsvService::CellData
            {
                cell.data(),
                cell.length() + 1
            };
        }
                      );
    }

    // ====================================================================== //
    // exported methods

    CsvHandle HOST_API_CALL readCsvData_dlx(const char* const filename, const ICsvService::CsvOptions csvOptions)
    {
        try
        {
            assertSaneString(filename);
            CsvHandle result;
            result.data = new IndexedCsvData(filename, csvOptions);
            return result;
        }
        CATCH_ALL_OWN(CsvHandle{nullptr})
    }

    CsvHandle HOST_API_CALL parseCsvData_dlx(const char* const rawData, const char* const origin, const ICsvService::CsvOptions csvOptions)
    {
        try
        {
            assertSaneString(rawData);
            assertSaneString(origin);
            CsvHandle result;
            result.data = new IndexedCsvData(rawData, origin, csvOptions);
            return result;
        }
        CATCH_ALL_OWN(CsvHandle{nullptr})
    }

    void HOST_API_CALL freeCsvData_dlx(CsvHandle* handle)
    {
        try
        {
            assertSanePointer(handle);
            assertSaneHandle(*handle);
            delete static_cast<IndexedCsvData*>(handle->data);
            handle->data = nullptr;
        }
        CATCH_ALL_OWN()
    }

    const char* HOST_API_CALL getOrigin_dlx(const CsvHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getOrigin().data();
        }
        CATCH_ALL_OWN(nullptr)
    }

    const size_t HOST_API_CALL getRowCount_dlx(const CsvHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getRowCount();
        }
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getMaxWidth_dlx(const CsvHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getMaxWidth();
        }
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getRowWidth_dlx(const CsvHandle handle, const size_t rowIndex)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getRowWidth(rowIndex);
        }
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getRowIndex_dlx(const CsvHandle handle, const char* const rowName)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getRowIndex(rowName);
        }
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getColumnIndex_dlx(const CsvHandle handle, const char* const columnName)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getColumnIndex(columnName);
        }
        CATCH_ALL_OWN(0)
    }

    void HOST_API_CALL reIndexRows_dlx(CsvHandle handle, const size_t columnIndex)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvDataMutable(handle).reIndexRows(columnIndex);
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL reIndexColumns_dlx(CsvHandle handle, const size_t rowIndex)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvDataMutable(handle).reIndexColumns(rowIndex);
        }
        CATCH_ALL_OWN()
    }

    ICsvService::RowData HOST_API_CALL reserveRowBuffer_dlx(const CsvHandle handle)
    {
        const auto nullRow = ICsvService::RowData {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            ICsvService::RowData result;
            const size_t width = toCsvData(handle).getMaxWidth();
            result.data = new ICsvService::CellData[width];
            result.size = width;
            return result;
        }
        CATCH_ALL_OWN(nullRow)
    }

    void HOST_API_CALL freeRowBuffer_dlx(ICsvService::RowData* buffer)
    {
        try
        {
            assertSanePointer(buffer);
            assertSanePointer(buffer->data);
            delete buffer->data;
            buffer->data = nullptr;
            buffer->size = 0;
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL getRow_dlx(const CsvHandle handle, ICsvService::RowData buffer, const size_t rowIndex)
    {
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string>& row = toCsvData(handle).getRow(rowIndex);
            transformRowToCData(row, buffer);
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL getRowByName_dlx(const CsvHandle handle, ICsvService::RowData buffer, const char* const rowName)
    {
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string>& row = toCsvData(handle).getRow(rowName);
            transformRowToCData(row, buffer);
        }
        CATCH_ALL_OWN()
    }

    ICsvService::CellData HOST_API_CALL getCell_dlx(const CsvHandle handle, const size_t rowIndex, const size_t columnIndex)
    {
        const auto nullCell = ICsvService::CellData {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const auto& cell = toCsvData(handle).getCell(rowIndex, columnIndex);
            return ICsvService::CellData {cell.data(), cell.size() + 1};
        }
        CATCH_ALL_OWN(nullCell)
    }

    ICsvService::CellData HOST_API_CALL getCellByName_dlx(const CsvHandle handle, const char* const rowName, const char* const columnName)
    {
        const auto nullCell = ICsvService::CellData {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const auto& cell = toCsvData(handle).getCell(rowName, columnName);
            return ICsvService::CellData {cell.data(), cell.size() + 1};
        }
        CATCH_ALL_OWN(nullCell)
    }
}
