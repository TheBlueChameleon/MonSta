#include "jsonservicedatabaseadapter.hpp"

JsonServiceDatabaseAdapter& JsonServiceDatabaseAdapter::getInstance()
{
    return static_cast<JsonServiceDatabaseAdapter&>(JsonServiceDatabase::getInstance());
}

void JsonServiceDatabaseAdapter::reset()
{
    database.clear();
}
