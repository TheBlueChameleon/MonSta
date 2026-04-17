#ifndef CSVSERVICE_HPP
#define CSVSERVICE_HPP

#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <services/ICsvService.hpp>

namespace CsvService
{
    class IndexedCsvFile
    {
        private:
            std::string origin;
            std::vector<std::vector<std::string>> cells;
            std::unordered_map<std::string, int> columnNames;

            void analyze(std::istream& stream);

        public:
            IndexedCsvFile(
                const std::filesystem::path& source,
                const ICsvService::CsvOptions csvOptions = ICsvService::CsvOptions()
            );
            IndexedCsvFile(
                const std::string& rawContent,
                const std::string& origin,
                const ICsvService::CsvOptions csvOptions = ICsvService::CsvOptions()
            );

            const std::string& getOrigin() const;
            const std::vector<std::vector<std::string>>& getCells() const;
    };
}

#endif // CSVSERVICE_HPP
