#include "errorservice.hpp"
#include "csvservice.hpp"
#include "services.hpp"

using namespace Services;
using namespace ErrorService;

namespace CsvService
{
    ICsvService::CsvHandle readCsvData(const std::filesystem::path& filename, const ICsvService::CsvOptions csvOptions)
    {
        auto result = csvService().readCsvData(filename.c_str(), csvOptions);
        rethrowHostError();
        return result;
    }

    ICsvService::CsvHandle parseCsvData(
        const std::string_view rawData,
        const std::string_view origin,
        const ICsvService::CsvOptions csvOptions
    )
    {
        auto result = csvService().parseCsvData(rawData.data(), origin.data(), csvOptions);
        rethrowHostError();
        return result;
    }

    void freeCsvData(ICsvService::CsvHandle& handle)
    {
        csvService().freeCsvData(&handle);
        rethrowHostError();
    }

    const std::string_view getOrigin(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().getOrigin(handle);
        rethrowHostError();
        return result;
    }

    const size_t getRowCount(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().getRowCount(handle);
        rethrowHostError();
        return result;
    }

    const size_t getMaxWidth(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().getMaxWidth(handle);
        rethrowHostError();
        return result;
    }

    const size_t getRowWidth(const ICsvService::CsvHandle handle, const size_t rowIndex)
    {
        auto result = csvService().getRowWidth(handle, rowIndex);
        rethrowHostError();
        return result;
    }

    const bool hasRow(const ICsvService::CsvHandle handle, const std::string_view rowName)
    {
        auto result = csvService().hasRow(handle, rowName.data());
        rethrowHostError();
        return result;
    }

    const bool hasColumn(const ICsvService::CsvHandle handle, const std::string_view columnName)
    {
        auto result = csvService().hasColumn(handle, columnName.data());
        rethrowHostError();
        return result;
    }

    const size_t getRowIndex(const ICsvService::CsvHandle handle, const std::string_view rowName)
    {
        auto result = csvService().getRowIndex(handle, rowName.data());
        rethrowHostError();
        return result;
    }

    const size_t getColumnIndex(const ICsvService::CsvHandle handle, const std::string_view columnName)
    {
        auto result = csvService().getColumnIndex(handle, columnName.data());
        rethrowHostError();
        return result;
    }

    void reIndexRows(ICsvService::CsvHandle handle, const size_t columnIndex)
    {
        csvService().reIndexRows(handle, columnIndex);
        rethrowHostError();
    }

    void reIndexColumns(ICsvService::CsvHandle handle, const size_t rowIndex)
    {
        csvService().reIndexColumns(handle, rowIndex);
        rethrowHostError();
    }

    MemoryService::StringViewArray reserveRowBuffer(const ICsvService::CsvHandle handle)
    {
        auto result = csvService().reserveRowBuffer(handle);
        rethrowHostError();
        return result;
    }

    void getRow(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const size_t rowIndex)
    {
        csvService().getRow(handle, buffer, rowIndex);
        rethrowHostError();
    }

    void getRow(const ICsvService::CsvHandle handle, MemoryService::StringViewArray& buffer, const size_t rowIndex)
    {
        return getRow(handle, buffer.getRaw(), rowIndex);
    }

    void getRowByName(const ICsvService::CsvHandle handle, IMemoryService::StringViewArray buffer, const std::string_view rowName)
    {
        csvService().getRowByName(handle, buffer, rowName.data());
        rethrowHostError();
    }

    void getRowByName(const ICsvService::CsvHandle handle, MemoryService::StringViewArray& buffer, const std::string_view rowName)
    {
        return getRowByName(handle, buffer.getRaw(), rowName);
    }

    MemoryService::StringArray getColumn(const ICsvService::CsvHandle handle, const size_t columnIndex)
    {
        auto result = csvService().getColumn(handle, columnIndex);
        rethrowHostError();
        return result;
    }

    MemoryService::StringArray getColumnByName(const ICsvService::CsvHandle handle, const std::string_view columnName)
    {
        auto result = csvService().getColumnByName(handle, columnName.data());
        rethrowHostError();
        return result;
    }

    std::string_view getCell(const ICsvService::CsvHandle handle, const size_t rowIndex, const size_t columnIndex)
    {
        const IMemoryService::StringView result = csvService().getCell(handle, rowIndex, columnIndex);
        rethrowHostError();
        return std::string_view(result.data, result.size - 1);
    }

    std::string_view getCellByName(
        const ICsvService::CsvHandle handle,
        const std::string_view rowName,
        const std::string_view columnName
    )
    {
        const IMemoryService::StringView result = csvService().getCellByName(handle, rowName.data(), columnName.data());
        rethrowHostError();
        return std::string_view(result.data, result.size - 1);
    }
}
