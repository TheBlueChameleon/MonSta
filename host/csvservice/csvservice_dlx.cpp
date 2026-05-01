#include <algorithm>
#include <cstring>
#include <string>

#include "errorservice/catchmacros.hpp"
#include "memoryservice/memoryservice.hpp"

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
        IMemoryService::StringViewArray buffer
    )
    {
        const auto toCellData = [](const std::string& cell)
        {
            return IMemoryService::StringView
            {
                const_cast<char*>(cell.data()),
                cell.length() + 1
            };
        };

        std::transform(row.begin(), row.end(),
                       buffer.data,
                       toCellData
                      );
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

    const bool HOST_API_CALL hasRow_dlx(const ICsvService::CsvHandle handle, const char* const rowName)
    {
        try
        {
            assertSaneHandle(handle);
            return toCsvData(handle).hasRow(rowName);
        }
        CATCH_ALL_OWN(false)
    }

    const bool HOST_API_CALL hasColumn_dlx(const ICsvService::CsvHandle handle, const char* const columnName)
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

    IMemoryService::StringViewArray HOST_API_CALL reserveRowBuffer_dlx(const ICsvService::CsvHandle handle)
    {
        const auto nullRow = IMemoryService::StringViewArray {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const size_t width = toCsvData(handle).getMaxWidth();
            return MemoryService::allocateStringViewArray(width);
        }
        CATCH_ALL_OWN(nullRow)
    }

    void HOST_API_CALL getRow_dlx(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const size_t rowIndex)
    {
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string>& row = toCsvData(handle).getRow(rowIndex);
            transformRowToCData(row, buffer);
        }
        CATCH_ALL_OWN()
    }

    void HOST_API_CALL getRowByName_dlx(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const char* const rowName)
    {
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string>& row = toCsvData(handle).getRow(rowName);
            transformRowToCData(row, buffer);
        }
        CATCH_ALL_OWN()
    }

    IMemoryService::StringArray HOST_API_CALL getColumn_dlx(const ICsvService::CsvHandle handle, const size_t columnIndex)
    {
        IMemoryService::StringArray nullData {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string> column = toCsvData(handle).getColumn(columnIndex);
            return MemoryService::copy(column);
        }
        CATCH_ALL_OWN(nullData)
    }

    IMemoryService::StringArray HOST_API_CALL getColumnByName_dlx(const ICsvService::CsvHandle handle, const char* const columnName)
    {
        IMemoryService::StringArray nullData {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const std::vector<std::string> column = toCsvData(handle).getColumn(columnName);
            return MemoryService::copy(column);
        }
        CATCH_ALL_OWN(nullData)
    }

    IMemoryService::StringView HOST_API_CALL getCell_dlx(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex)
    {
        const auto nullCell = IMemoryService::StringView {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const auto& cell = toCsvData(handle).getCell(rowIndex, columnIndex);
            return MemoryService::wrap(cell);
        }
        CATCH_ALL_OWN(nullCell)
    }

    IMemoryService::StringView HOST_API_CALL getCellByName_dlx(const ICsvService::CsvHandle handle, const char* const rowName, const char* const columnName)
    {
        const auto nullCell = IMemoryService::StringView {nullptr, 0};
        try
        {
            assertSaneHandle(handle);
            const auto& cell = toCsvData(handle).getCell(rowName, columnName);
            return MemoryService::wrap(cell);
        }
        CATCH_ALL_OWN(nullCell)
    }

}
