#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

#include <csv.h>

#include "errorservice/errors.hpp"

#include "fileservice/fileservice.hpp"

#include "csvservice.hpp"

#include <utility>
using namespace std::string_literals;

namespace CsvService
{
    struct InsertionBuffer
    {
        IndexedCsvData::RowType currentLine;
        IndexedCsvData::TableType& table;
        std::vector<size_t>& widths;
        size_t maxWidth = 0;

        InsertionBuffer(
            IndexedCsvData::TableType& table,
            std::vector<size_t>& widths
        ) :
            table(table), widths(widths)
        {}
    };

    static void processCell(void* cellContentString, size_t len, void* target)
    {
        auto& insertionBuffer = *static_cast<InsertionBuffer*>(target);
        insertionBuffer.currentLine.emplace_back(static_cast<const char* const>(cellContentString));
    }

    static void processLine([[maybe_unused]] int lineBreakCode, void* target)
    {
        auto& insertionBuffer = *static_cast<InsertionBuffer*>(target);
        size_t currentWidth = insertionBuffer.currentLine.size();

        insertionBuffer.table.push_back(std::move(insertionBuffer.currentLine));
        insertionBuffer.widths.push_back(currentWidth);

        if (insertionBuffer.maxWidth < currentWidth)
        {
            insertionBuffer.maxWidth = currentWidth;
        }

        insertionBuffer.currentLine.clear();
    }

    static struct csv_parser getParser(const ICsvService::CsvOptions& csvOptions)
    {
        struct csv_parser parser;

        if (csv_init(&parser, CSV_APPEND_NULL) != 0)
        {
            throw CsvError("Could not initialize parser");
        }

        csv_set_delim(&parser, csvOptions.delimiter);
        csv_set_quote(&parser, csvOptions.quoteChar);

        return parser;
    }

    void IndexedCsvData::parse(
        std::istream& stream,
        const ICsvService::CsvOptions& csvOptions
    )
    {
        if (!stream)
        {
            throw CsvError("Could not read from "s + origin);
        }

        auto parser = getParser(csvOptions);
        auto const readSize = 1024;
        auto readBuffer = new char[readSize];
        auto insertBuffer = InsertionBuffer(table, widths);

        while (stream)
        {
            stream.read(readBuffer, readSize);
            size_t bytes_read = stream.gcount();

            if (csv_parse(&parser, readBuffer, bytes_read, processCell, processLine, &insertBuffer) != bytes_read)
            {
                throw CsvError("Error while parsing "s + origin + ": "s + csv_strerror(csv_error(&parser)));
            }
        }
        csv_fini(&parser, processCell, processLine, &insertBuffer);

        maxWidth = insertBuffer.maxWidth;

        delete readBuffer;
        csv_free(&parser);
    }

    static void generateColumnNames(
        std::unordered_map<std::string, int>& indices,
        const int idx,
        IndexedCsvData::TableType& table
    )
    {
        if (idx < 0 || idx >= table.size())
        {
            throw CsvError("Illegal header row index "s + std::to_string(idx));
        }

        for (int i = 0; const auto& element : table[idx])
        {
            const auto [it, emplaced] = indices.try_emplace(element, i);
            if (!emplaced)
            {
                throw CsvError("Duplicate column name: "s + element);
            }

            ++i;
        }
    }

    static void generateRowNames(
        std::unordered_map<std::string, int>& indices,
        const int idx,
        IndexedCsvData::TableType& table
    )
    {
        if (idx < 0)
        {
            throw CsvError("Illegal key column index "s + std::to_string(idx));
        }

        for (int i = 0; const auto& row : table)
        {
            if (idx >= row.size())
            {
                throw CsvError("Illegal key column index "s + std::to_string(idx) + "\n"
                               "(row "+ std::to_string(i) + " has less columns than that)");
            }

            const auto& element = row[idx];
            const auto [it, emplaced] = indices.try_emplace(element, i);
            if (!emplaced)
            {
                throw CsvError("Duplicate row name: "s + element);
            }

            ++i;
        }

        const auto& headerRow = table[idx];
    }


    void IndexedCsvData::generateIndices(const ICsvService::CsvOptions& csvOptions)
    {
        if (csvOptions.headerRow != -1)
        {
            generateColumnNames(columnNames, csvOptions.headerRow, table);
        }

        if (csvOptions.keyColumn != -1)
        {
            generateRowNames(rowNames, csvOptions.keyColumn, table);
        }
    }

    IndexedCsvData::IndexedCsvData(
        const std::filesystem::__cxx11::path& source,
        const ICsvService::CsvOptions csvOptions
    ) : origin(source)
    {
        auto fileStream = FileService::getInputStream(source);
        parse(fileStream, csvOptions);
        generateIndices(csvOptions);
    }

    IndexedCsvData::IndexedCsvData(
        const std::string& rawContent,
        const std::string& origin,
        const ICsvService::CsvOptions csvOptions
    ) : origin(origin)
    {
        std::istringstream data(rawContent);
        parse(data, csvOptions);
        generateIndices(csvOptions);
    }

    const std::string& IndexedCsvData::getOrigin() const
    {
        return origin;
    }

    const size_t IndexedCsvData::getRowCount() const
    {
        return table.size();
    }

    const std::vector<size_t>& IndexedCsvData::getWidths() const
    {
        return widths;
    }

    size_t IndexedCsvData::getMaxWidth() const
    {
        return maxWidth;
    }

    const int IndexedCsvData::getRowIndex(const std::string& rowName) const
    {
        auto it = rowNames.find(rowName);
        if (it == rowNames.end())
        {
            throw CsvError("Unknown row name: "s + rowName);
        }

        return it->second;
    }

    const int IndexedCsvData::getColumnIndex(const std::string& columnName) const
    {
        auto it = columnNames.find(columnName);
        if (it == columnNames.end())
        {
            throw CsvError("Unknown column name: "s + columnName);
        }

        return it->second;
    }

    const std::unordered_map<std::string, int>& IndexedCsvData::getColumnNameToIndexMap() const
    {
        return columnNames;
    }

    const std::unordered_map<std::string, int>& IndexedCsvData::getRowNameToIndexMap() const
    {
        return rowNames;
    }

    void IndexedCsvData::reIndexByColumn(const int column)
    {
        rowNames.clear();
        generateColumnNames(rowNames, column, table);
    }

    const IndexedCsvData::TableType& IndexedCsvData::getTable() const
    {
        return table;
    }

    const IndexedCsvData::RowType& IndexedCsvData::getRow(const int row) const
    {
        if (row < 0 || row >= table.size())
        {
            throw CsvError("Invalid row index "s + std::to_string(row) + " while accessing CSV data from " + origin);
        }

        return table[row];
    }

    const IndexedCsvData::RowType& IndexedCsvData::getRow(const std::string& rowName) const
    {
        return getRow(getRowIndex(rowName));
    }

    const IndexedCsvData::CellType& IndexedCsvData::getCell(const int row, const int column) const
    {
        const auto& rowData = getRow(row);

        if (column < 0 || column >= rowData.size())
        {
            throw CsvError("Invalid column index "s + std::to_string(column) + " while accessing CSV data from " + origin);
        }

        return rowData[column];
    }

    const IndexedCsvData::CellType& IndexedCsvData::getCell(const std::string& rowName, const std::string& columnName) const
    {
        const auto& rowData = getRow(rowName);
        return rowData[getColumnIndex(columnName)];
    }

}
