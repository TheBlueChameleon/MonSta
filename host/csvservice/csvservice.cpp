#include <fstream>

#include <csv.h>

#include "fileservice/fileservice.hpp"

#include "csvservice.hpp"

namespace CsvService
{
    void IndexedCsvFile::analyze(std::istream& stream)
    {}

    IndexedCsvFile::IndexedCsvFile(
        const std::filesystem::__cxx11::path& source,
        const ICsvService::CsvOptions csvOptions
    ) :
        origin(source)
    {
        auto f = FileService::getInputStream(source);
        analyze(f);
    }

    IndexedCsvFile::IndexedCsvFile(
        const std::string& rawContent,
        const std::string& origin,
        const ICsvService::CsvOptions csvOptions
    ) :
        origin(origin)
    {
        std::istringstream data(rawContent);
        analyze(data);
    }

    const std::string& IndexedCsvFile::getOrigin() const
    {
        return origin;
    }

    const std::vector<std::vector<std::string> >& IndexedCsvFile::getCells() const
    {
        return cells;
    }

}
