#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

#include <CallingConventions.hpp>

#include "JsonService/IJsonService_Database.hpp"
#include "JsonService/IJsonService_ItemAccess.hpp"
#include "JsonService/IJsonService_SchemaBuilder.hpp"
#include "JsonService/IJsonService_Types.hpp"

struct IJsonService
{
    IJsonService_Database database;
    IJsonService_ItemAccess itemAccess;
    IJsonService_SchemaBuilder schemaBuilder;
};

#endif // IJSONSERVICE_HPP
