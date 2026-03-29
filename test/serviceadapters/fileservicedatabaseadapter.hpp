#ifndef FILESERVICEDATABASEADAPTER_H
#define FILESERVICEDATABASEADAPTER_H

#include "fileservice/fileservicedatabase.hpp"
#include "fileservice/synchronizedostream.hpp"

class FileServiceDatabaseAdapter : public FileService::FileServiceDatabase
{
    protected:
        FileServiceDatabaseAdapter() = default;

    public:
        static FileServiceDatabaseAdapter& getInstance();
        void reset();
};

#endif // FILESERVICEDATABASEADAPTER_H
