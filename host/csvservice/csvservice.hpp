#ifndef CSVSERVICE_HPP
#define CSVSERVICE_HPP

#include <filesystem>

namespace rapidcsv
{
    class Document;
}

namespace CsvService
{
    void setHeaderColumnId(const int id);
    void setHeaderRowId(const int id);

    void setSeparator(const char separator);
    void setTrim(const bool trim);
    void setHasCR(const bool hasCR);
    void setQuotedLineBreaks(const bool quotedLineBreaks);
    void setAutoQuote(const bool autoQuote);
    void setQuoteChar(const char quoteChar);

    void setSkipCommentLines(const bool skipComments);
    void setCommentIndicator(const char commentIndicator);
    void setSkipEmptyLines(const bool skipEmptyLines);

    rapidcsv::Document read(const std::filesystem::path& file);
}

#endif // CSVSERVICE_HPP
