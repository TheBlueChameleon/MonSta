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
            std::unordered_map<std::string, int> columnNames;
            std::unordered_map<std::string, int> rowNames;
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
            size_t getMaxWidth() const;

            const int getRowIndex(const std::string& rowName) const;
            const int getColumnIndex(const std::string& columnName)const ;
            const std::unordered_map<std::string, int>& getColumnNameToIndexMap() const;
            const std::unordered_map<std::string, int>& getRowNameToIndexMap() const;

            void reIndexByColumn(const int column);

            const TableType& getTable() const;
            const RowType&   getRow(const int row) const;
            const RowType&   getRow(const std::string& rowName) const;
            const CellType&  getCell(const int row, const int column) const;
            const CellType&  getCell(const std::string& rowName, const std::string& columnName) const;
    };
}

#endif // CSVSERVICE_HPP
