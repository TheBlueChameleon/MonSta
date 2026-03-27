#ifndef FILESERVICEDATABASETESTADAPTER_HPP
#define FILESERVICEDATABASETESTADAPTER_HPP

#include "fileservice/fileservicedatabase.hpp"
#include "fileservice/synchronizedostream.hpp"

class FileServiceDatabaseTestAdapter : public FileService::FileServiceDatabase
{
    protected:
        FileServiceDatabaseTestAdapter() = default;

    public:
        static FileServiceDatabaseTestAdapter& getInstance();
        void reset();
};

#endif // FILESERVICEDATABASETESTADAPTER_HPP
