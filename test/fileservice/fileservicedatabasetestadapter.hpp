#ifndef FILESERVICEDATABASETESTADAPTER_HPP
#define FILESERVICEDATABASETESTADAPTER_HPP

#include "fileservice/fileservicedatabase.hpp"
#include "fileservice/synchronizedostream.hpp"

class FileServiceDatabaseTestAdapter : public FileService::FileServiceDatabase
{
    public:
        FileServiceDatabaseTestAdapter();
};

#endif // FILESERVICEDATABASETESTADAPTER_HPP
