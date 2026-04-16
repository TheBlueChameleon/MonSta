#ifndef CSVSERVICE_DLX_HPP
#define CSVSERVICE_DLX_HPP

namespace CsvService
{
    struct CsvHandle
    {
        void* data;
    };

    void setHeaderColumnId_dlx(const int id);
    void setHeaderRowId_dlx(const int id);

    void setSeparator_dlx(const char separator);
    void setTrim_dlx(const bool trim);
    void setHasCR_dlx(const bool hasCR);
    void setQuotedLineBreaks_dlx(const bool quotedLineBreaks);
    void setAutoQuote_dlx(const bool autoQuote);
    void setQuoteChar_dlx(const char quoteChar);

    void setSkipCommentLines_dlx(const bool skipComments);
    void setCommentIndicator_dlx(const char commentIndicator);
    void setSkipEmptyLines_dlx(const bool skipEmptyLines);

    CsvHandle read_dlx(const char* const file);
}

#endif // CSVSERVICE_DLX_HPP
