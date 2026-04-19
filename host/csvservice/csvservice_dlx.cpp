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

    static void assertSaneHandle(const ICsvService::CsvHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw InvalidUserInput("Attempted to process null CSV handle");
        }
    }

    static const IndexedCsvData& toCsvData(const ICsvService::CsvHandle handle)
    {
        return *static_cast<const IndexedCsvData*>(handle.data);
    }

    static IndexedCsvData& toCsvDataMutable(ICsvService::CsvHandle handle)
    {
        return *static_cast<IndexedCsvData*>(handle.data);
    }

    static void transformRowToCData(
        const std::vector<std::string>& row,
        ICsvService::RowData buffer
    )
    {
        const auto toCellData = [](const std::string& cell)
        {
            return ICsvService::CellData
            {
                cell.data(),
                cell.length() + 1
            };
        };

        std::transform(row.begin(), row.end(),
                       buffer.data,
                       toCellData
                      );
    }

    static ICsvService::ColumnData copyColumnToCData(const std::vector<std::string>& column)
    {
        ICsvService::ColumnData result;

        const size_t size = column.size();
        result.data = new ICsvService::CellData[size];
        result.size = size;

        const auto copyToCells = [](const std::string& cellString)
        {
            ICsvService::CellData cell;

            const size_t size = cellString.size() + 1;
            cell.data = new char[size];
            cell.size = size;

            std::strncpy(const_cast<char*>(cell.data), cellString.data(), size);

            return cell;
        };

        std::transform(column.begin(), column.end(),
                       result.data,
                       copyToCells
                      );

        return result;
    }

    // ====================================================================== //
    // exported methods

    ICsvService::CsvHandle readCsvData_dlx(const char* const filename, const ICsvService::CsvOptions csvOptions)
    {
        try
        {
            assertSaneString(filename);
            ICsvService::CsvHandle result;
            result.data = new IndexedCsvData(filename, csvOptions);
            return result;
        }
        CATCH_ALL_OWN(ICsvService::CsvHandle{nullptr})
    }

    ICsvService::CsvHandle parseCsvData_dlx(const char* const rawData, const char* const origin, const ICsvService::CsvOptions csvOptions)
    {
        try
        {
            assertSaneString(rawData);
            assertSaneString(origin);
            ICsvService::CsvHandle result;
            result.data = new IndexedCsvData(rawData, origin, csvOptions);
            return result;
        }
        CATCH_ALL_OWN(ICsvService::CsvHandle{nullptr})
    }

    void HOST_API_CALL freeCsvData_dlx(ICsvService::CsvHandle* handle)
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

    const char* HOST_API_CALL getOrigin_dlx(const ICsvService::CsvHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getOrigin().data();
        }
        CATCH_ALL_OWN(nullptr)
    }

    const size_t HOST_API_CALL getRowCount_dlx(const ICsvService::CsvHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getRowCount();
        }
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getMaxWidth_dlx(const ICsvService::CsvHandle handle)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getMaxWidth();
        }
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getRowWidth_dlx(const ICsvService::CsvHandle handle, const size_t rowIndex)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getRowWidth(rowIndex);
        }
        CATCH_ALL_OWN(0)
    }

    const bool hasRow_dlx(const ICsvService::CsvHandle handle, const char* const rowName)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).hasRow(rowName);
        }
        CATCH_ALL_OWN(false)
    }

    const bool hasColumn_dlx(const ICsvService::CsvHandle handle, const char* const columnName)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).hasColumn(columnName);
        }
        CATCH_ALL_OWN(false)
    }

    const size_t HOST_API_CALL getRowIndex_dlx(const ICsvService::CsvHandle handle, const char* const rowName)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getRowIndex(rowName);
        }
        CATCH_ALL_OWN(0)
    }

    const size_t HOST_API_CALL getColumnIndex_dlx(const ICsvService::CsvHandle handle, const char* const columnName)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).getColumnIndex(columnName);
        }
        CATCH_ALL_OWN(0)
    }

    void HOST_API_CALL reIndexRows_dlx(ICsvService::CsvHandle handle, const size_t columnIndex)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvDataMutable(handle).reIndexRows(columnIndex);
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL reIndexColumns_dlx(ICsvService::CsvHandle handle, const size_t rowIndex)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvDataMutable(handle).reIndexColumns(rowIndex);
        }
        CATCH_ALL_OWN()
    }

    ICsvService::RowData HOST_API_CALL reserveRowBuffer_dlx(const ICsvService::CsvHandle handle)
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

    void HOST_API_CALL getRow_dlx(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const size_t rowIndex)
    {
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string>& row = toCsvData(handle).getRow(rowIndex);
            transformRowToCData(row, buffer);
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL getRowByName_dlx(const ICsvService::CsvHandle handle, ICsvService::RowData buffer, const char* const rowName)
    {
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string>& row = toCsvData(handle).getRow(rowName);
            transformRowToCData(row, buffer);
        }
        CATCH_ALL_OWN()
    }

    ICsvService::ColumnData HOST_API_CALL getColumn_dlx(const ICsvService::CsvHandle handle, const size_t columnIndex)
    {
        ICsvService::ColumnData nullData {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string> column = toCsvData(handle).getColumn(columnIndex);
            return copyColumnToCData(column);
        }
        CATCH_ALL_OWN(nullData)
    }

    ICsvService::ColumnData HOST_API_CALL getColumnByName_dlx(const ICsvService::CsvHandle handle, const char* const columnName)
    {
        ICsvService::ColumnData nullData {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string> column = toCsvData(handle).getColumn(columnName);
            return copyColumnToCData(column);
        }
        CATCH_ALL_OWN(nullData)
    }

    void HOST_API_CALL freeColumnBuffer_dlx(ICsvService::ColumnData* columnData)
    {
        try
        {
            assertSanePointer(columnData);
            assertSanePointer(columnData->data);

            for (int i = 0; i < columnData->size; ++i)
            {
                assertSanePointer(columnData->data[i].data);
                delete columnData->data[i].data;
                columnData->data[i].data = nullptr;
                columnData->data[i].size = 0;
            }
            delete columnData->data;
            columnData->data = nullptr;
            columnData->size = 0;
        }
        CATCH_ALL_OWN()
    }

    ICsvService::CellData HOST_API_CALL getCell_dlx(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex)
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

    ICsvService::CellData HOST_API_CALL getCellByName_dlx(const ICsvService::CsvHandle handle, const char* const rowName, const char* const columnName)
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
