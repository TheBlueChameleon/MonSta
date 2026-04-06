#ifndef JSONSERVICE_SCHEMABUILDER_DLX_HPP
#define JSONSERVICE_SCHEMABUILDER_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    const IJsonServiceTypes::JsonSchemaBuilderHandle        HOST_API_CALL instantiateSchemaBuilder_dlx();
    const IJsonServiceTypes::JsonSubSchemaBuilderHandle     HOST_API_CALL instantiateSubSchemaBuilder_dlx(const char* const name);
    const IJsonServiceTypes::JsonSchemaElementBuilderHandle HOST_API_CALL instantiateSchemaElementBuilder_dlx(const char* const name);

    void HOST_API_CALL freeSchemaBuilder_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle& handle);
    void HOST_API_CALL freeSubSchemaBuilder_dlx(IJsonServiceTypes::JsonSubSchemaBuilderHandle& handle);
    void HOST_API_CALL freeSchemaElementBuilder_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle);

    /*
     * json schema builder ops:
     * ???
     */
}

#endif // JSONSERVICE_SCHEMABUILDER_DLX_HPP
