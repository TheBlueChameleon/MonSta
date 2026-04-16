#include <rapidcsv.h>

#include "fileservice/fileservice.hpp"

#include "csvservice.hpp"

using namespace rapidcsv;

namespace CsvService
{
    LabelParams labelParams;
    SeparatorParams separatorParams;
    LineReaderParams lineReaderParams;

    void setHeaderColumnId(const int id)
    {
        labelParams.mColumnNameIdx = id;
    }

    void setHeaderRowId(const int id)
    {
        labelParams.mRowNameIdx = id;
    }

    void setSeparator(const char separator)
    {
        separatorParams.mSeparator = separator;
    }

    void setTrim(const bool trim)
    {
        separatorParams.mTrim = trim;
    }

    void setHasCR(const bool hasCR)
    {
        separatorParams.mHasCR = hasCR;
    }

    void setQuotedLineBreaks(const bool quotedLineBreaks)
    {
        separatorParams.mQuotedLinebreaks = quotedLineBreaks;
    }

    void setAutoQuote(const bool autoQuote)
    {
        separatorParams.mAutoQuote = autoQuote;
    }

    void setQuoteChar(const char quoteChar)
    {
        separatorParams.mQuoteChar = quoteChar;
    }

    void setSkipCommentLines(const bool skipComments)
    {
        lineReaderParams.mSkipCommentLines = skipComments;
    }

    void setCommentIndicator(const char commentIndicator)
    {
        lineReaderParams.mCommentPrefix = commentIndicator;
    }

    void setSkipEmptyLines(const bool skipEmptyLines)
    {
        lineReaderParams.mSkipEmptyLines = skipEmptyLines;
    }

    Document read(const std::filesystem::__cxx11::path& file)
    {
        return Document(
                   FileService::getInputBasePath() / file,
                   labelParams,
                   separatorParams,
                   ConverterParams(),
                   lineReaderParams
               );
    }

}
