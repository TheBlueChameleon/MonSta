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

    const std::string_view JsonSchemaElementBuilder::getName() const
    {
        return JsonService::seb_getName(handle);
    }

    const IJsonServiceTypes::JsonHandle JsonSchemaElementBuilder::getJson() const
    {
        return JsonService::seb_getJson(handle);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setJson(const IJsonServiceTypes::JsonHandle sourceHandle)
    {
        JsonService::seb_setJsonByHandle(handle, sourceHandle);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setJson(const std::string_view rawJson)
    {
        JsonService::seb_setJsonByParseable(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setProperty(const std::string_view key, const std::string_view rawJson)
    {
        JsonService::seb_setProperty(handle, key, rawJson);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setType(const IJsonServiceTypes::JsonType type)
    {
        JsonService::seb_setType(handle, type);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setEnum(const std::string_view rawJson)
    {
        JsonService::seb_setEnum(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setTypedArray(const IJsonServiceTypes::JsonType type)
    {
        JsonService::seb_setTypedArray(handle, type);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setEnumArray(const std::string_view rawJson)
    {
        JsonService::seb_setEnumArray(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDefault(const std::string_view rawJson)
    {
        JsonService::seb_setDefault(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setMinimum(const std::string_view rawJson)
    {
        JsonService::seb_setMinimum(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setMaximum(const std::string_view rawJson)
    {
        JsonService::seb_setMaximum(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDescription(const std::string_view value)
    {
        JsonService::seb_setDescription(handle, value);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setTitle(const std::string_view value)
    {
        JsonService::seb_setTitle(handle, value);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setReference(const std::string_view value)
    {
        JsonService::seb_setReference(handle, value);
        return *this;
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

    JsonSchemaBuilder& JsonSchemaBuilder::addRequired(const std::string_view requiredPropertyName)
    {
        JsonService::sb_addRequired(handle, requiredPropertyName);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addAllOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addAllOfRequirement(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addAnyOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addAnyOfRequirement(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addOneOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addOneOfRequirement(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addNoneOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addNoneOfRequirement(handle, rawJson);
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

    IJsonServiceTypes::JsonHandle JsonSchemaBuilder::buildAndAdd(const IJsonServiceTypes::JsonTag tag) const
    {
        return JsonService::sb_buildAndAdd(handle, tag);
    }

} // namespace FileService
