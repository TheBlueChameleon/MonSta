#include "jsonservice_schemabuilder.hpp"
#include "schemabuilder_wrapper.hpp"

namespace JsonService
{
    // ====================================================================== //
    // JsonSchemaElementBuilder

    JsonSchemaElementBuilder::JsonSchemaElementBuilder(const std::string_view name) :
        handle(JsonService::instantiateSchemaElementBuilder(name)),
        selfManaged(true)
    {}

    JsonSchemaElementBuilder::JsonSchemaElementBuilder(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle) :
        handle(handle),
        selfManaged(false)
    {}

    JsonSchemaElementBuilder::~JsonSchemaElementBuilder()
    {
        if (selfManaged)
        {
            JsonService::freeSchemaElementBuilder(handle);
        }
    }


    // ====================================================================== //
    // JsonSchemaBuilder

    JsonSchemaBuilder::JsonSchemaBuilder(const std::string_view name) :
        handle(JsonService::instantiateSchemaBuilder(name)),
        selfManaged(true)
    {}

    JsonSchemaBuilder::JsonSchemaBuilder(const IJsonServiceTypes::JsonSchemaBuilderHandle handle) :
        handle(handle),
        selfManaged(false)
    {}

    JsonSchemaBuilder::~JsonSchemaBuilder()
    {
        if (selfManaged)
        {
            JsonService::freeSchemaBuilder(handle);
        }
    }

    JsonSchemaBuilder& JsonSchemaBuilder::setAdditionalProperties(const std::string_view rawJson)
    {
        JsonService::sb_setAdditionalProperties(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addRequired(const std::string_view required)
    {
        JsonService::sb_addRequired(handle, required);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addAllOfReference(const std::string_view schemaName)
    {
        JsonService::sb_addAllOfReference(handle, schemaName);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addAnyOfReference(const std::string_view schemaName)
    {
        JsonService::sb_addAnyOfReference(handle, schemaName);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addOneOfReference(const std::string_view schemaName)
    {
        JsonService::sb_addOneOfReference(handle, schemaName);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addNotReference(const std::string_view schemaName)
    {
        JsonService::sb_addNotReference(handle, schemaName);
        return *this;
    }

    IJsonServiceTypes::ModifiableJsonHandle JsonSchemaBuilder::addElement(const std::string_view name)
    {
        return JsonService::sb_addElementByName(handle, name);
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addElement(const std::string_view name, const std::string rawJson)
    {
        JsonService::sb_addElementByParseable(handle, name, rawJson);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addReference(
        const std::string_view propertyName,
        const std::string_view schemaName,
        const IJsonServiceTypes::JsonType type,
        bool setDefaults
    )
    {
        JsonService::sb_addReferenceByName(handle, propertyName, schemaName, type, setDefaults);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addReference(
        const std::string_view propertyName,
        const JsonSchemaBuilder& subSchema,
        const IJsonServiceTypes::JsonType type,
        bool setDefaults
    )
    {
        JsonService::sb_addReferenceByType(handle, propertyName, subSchema.handle, type, setDefaults);
        return *this;
    }

    JsonSchemaBuilder JsonSchemaBuilder::addSubSchema(const std::string_view name)
    {
        return JsonSchemaBuilder(
                   JsonService::sb_addSubSchemaByName(handle, name)
               );
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addSubSchema(const JsonSchemaBuilder& subSchema)
    {
        JsonService::sb_addSubSchemaByType(handle, subSchema.handle);
        return *this;
    }

    JsonSchemaElementBuilder JsonSchemaBuilder::addProperty(const std::string_view name)
    {
        return JsonSchemaElementBuilder(
                   JsonService::sb_addPropertyByName(handle, name)
               );
    }

    JsonSchemaElementBuilder JsonSchemaBuilder::addProperty(const std::string_view name, IJsonServiceTypes::JsonType type)
    {
        return JsonSchemaElementBuilder(
                   JsonService::sb_addPropertyByNameWithType(handle, name, type)
               );
    }

    IJsonServiceTypes::JsonHandle JsonSchemaBuilder::build(const IJsonServiceTypes::JsonTag tag) const
    {
        return JsonService::sb_buildAndAdd(handle, tag);
    }

} // namespace FileService


