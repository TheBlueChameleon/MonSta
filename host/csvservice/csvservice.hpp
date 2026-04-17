#ifndef CSVSERVICE_HPP
#define CSVSERVICE_HPP

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include <services/ICsvService.hpp>

namespace CsvService
{
    const ICsvService exportService();

    class IndexedCsvData
    {
        public:
            using CellType  = std::string;
            using RowType   = std::vector<CellType>;
            using TableType = std::vector<RowType>;

        private:
            TableType   table;
            std::string origin;
            std::unordered_map<std::string, size_t> columnNames;
            std::unordered_map<std::string, size_t> rowNames;
            std::vector<size_t> widths;
            size_t              maxWidth;

            void parse(
                std::istream& stream,
                const ICsvService::CsvOptions& csvOptions
            );
            void generateIndices(const ICsvService::CsvOptions& csvOptions);

        public:
            IndexedCsvData(
                const std::filesystem::path& source,
                const ICsvService::CsvOptions csvOptions = ICsvService::CsvOptions()
            );
            IndexedCsvData(
                const std::string& rawContent,
                const std::string& origin,
                const ICsvService::CsvOptions csvOptions = ICsvService::CsvOptions()
            );

            const std::string& getOrigin() const;

            const size_t getRowCount() const;
            const std::vector<size_t>& getWidths() const;
            const size_t getMaxWidth() const;
            const size_t getRowWidth(const size_t rowIndex) const;

            const size_t getRowIndex(const std::string& rowName) const;
            const size_t getColumnIndex(const std::string& columnName) const;
            const std::unordered_map<std::string, size_t>& getColumnNameToIndexMap() const;
            const std::unordered_map<std::string, size_t>& getRowNameToIndexMap() const;

            void reIndexRows(const size_t columnIndex);
            void reIndexColumns(const size_t rowIndex);

            const TableType& getTable() const;
            const RowType&   getRow(const size_t rowIndex) const;
            const RowType&   getRow(const std::string& rowName) const;
            const CellType&  getCell(const size_t rowIndex, const size_t columnIndex) const;
            const CellType&  getCell(const std::string& rowName, const std::string& columnName) const;
    };
}

#endif // CSVSERVICE_HPP
