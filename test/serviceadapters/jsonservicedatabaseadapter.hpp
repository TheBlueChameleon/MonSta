#ifndef JSONSERVICEDATABASEADAPTER_HPP
#define JSONSERVICEDATABASEADAPTER_HPP

#include <jsonservice/jsonservicedatabase.hpp>

class JsonServiceDatabaseAdapter : public JsonService::JsonServiceDatabase
{
    protected:
        JsonServiceDatabaseAdapter() = default;

    public:
        static JsonServiceDatabaseAdapter& getInstance();
        void reset();
};

#endif // JSONSERVICEDATABASEADAPTER_HPP
