#ifndef JSONSERVICE_SCHEMABUILDER_DLX_HPP
#define JSONSERVICE_SCHEMABUILDER_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    const IJsonServiceTypes::JsonSchemaBuilderHandle    HOST_API_CALL instantiateSchemaBuilder_dlx();
    const IJsonServiceTypes::JsonSubSchemaBuilderHandle HOST_API_CALL instantiateSubSchemaBuilder_dlx();
    const IJsonServiceTypes::JsonElementBuilderHandle   HOST_API_CALL instantiateElementBuilder_dlx();

    void HOST_API_CALL freeSchemaBuilder_dlx(const IJsonServiceTypes::JsonSchemaBuilderHandle*);
    void HOST_API_CALL freeSubSchemaBuilder_dlx(const IJsonServiceTypes::JsonSubSchemaBuilderHandle*);
    void HOST_API_CALL freeElementBuilder_dlx(const IJsonServiceTypes::JsonElementBuilderHandle*);

    /*
     * json schema builder ops:
     * ???
     */
}

#endif // JSONSERVICE_SCHEMABUILDER_DLX_HPP
