#include "errorservice/catchmacros.hpp"

#include "handleconverter.hpp"
#include "jsonschemabuilder.hpp"
#include "jsonservice_schemabuilder_dlx.hpp"

namespace JsonService
{
    IJsonServiceTypes::JsonSchemaBuilderHandle HOST_API_CALL instantiateSchemaBuilder_dlx()
    {
        try
        {
            return toJsonSchemaBuilderHandle(*new JsonSchemaBuilder);
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaBuilderHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaBuilderHandle(nullptr))
    }

    IJsonServiceTypes::JsonSubSchemaBuilderHandle HOST_API_CALL instantiateSubSchemaBuilder_dlx(const char* const name)
    {
        try
        {
            return toJsonSubSchemaBuilderHandle(*new JsonSubSchemaBuilder(name));
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSubSchemaBuilderHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSubSchemaBuilderHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSubSchemaBuilderHandle(nullptr))
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle instantiateSchemaElementBuilder_dlx(const char* const name)
    {
        try
        {
            return toJsonSchemaElementBuilderHandle(*new JsonSchemaElementBuilder(name));
        }
        CATCH_ABSTRACT_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle(nullptr))
        CATCH_JSON_ERROR(IJsonServiceTypes::JsonSchemaElementBuilderHandle(nullptr))
        CATCH_STD_EXCEPTION(IJsonServiceTypes::JsonSchemaElementBuilderHandle(nullptr))
    }

    void HOST_API_CALL freeSchemaBuilder_dlx(IJsonServiceTypes::JsonSchemaBuilderHandle& handle)
    {
        try
        {
            assertSaneHandle(handle);
            delete &toSchemaBuilder(handle);
            handle.data = nullptr;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL freeSubSchemaBuilder_dlx(IJsonServiceTypes::JsonSubSchemaBuilderHandle& handle)
    {
        try
        {
            assertSaneHandle(handle);
            delete &toSubSchemaBuilder(handle);
            handle.data = nullptr;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

    void HOST_API_CALL freeSchemaElementBuilder_dlx(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle)
    {
        try
        {
            assertSaneHandle(handle);
            delete &toSchemaElementBuilder(handle);
            handle.data = nullptr;
        }
        CATCH_ABSTRACT_ERROR()
        CATCH_JSON_ERROR()
        CATCH_STD_EXCEPTION()
    }

}
