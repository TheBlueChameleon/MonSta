#include "jsonservice_schemabuilder.hpp"
#include "schemabuilder_wrapper.hpp"

namespace JsonService
{
    // ====================================================================== //
    // JsonSchemaElementBuilder

    JsonSchemaElementBuilderWrapper::JsonSchemaElementBuilderWrapper(const std::string_view name) :
        handle(JsonService::instantiateSchemaElementBuilder(name)),
        selfManaged(true)
    {}

    JsonSchemaElementBuilderWrapper::JsonSchemaElementBuilderWrapper(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle) :
        handle(handle),
        selfManaged(false)
    {}

    JsonSchemaElementBuilderWrapper::~JsonSchemaElementBuilderWrapper()
    {
        if (selfManaged)
        {
            JsonService::freeSchemaElementBuilder(handle);
        }
    }

    const std::string_view JsonSchemaElementBuilderWrapper::getName() const
    {
        return JsonService::seb_getName(handle);
    }

    const IJsonServiceTypes::JsonHandle JsonSchemaElementBuilderWrapper::getJson() const
    {
        return JsonService::seb_getJson(handle);
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setJson(const IJsonServiceTypes::JsonHandle sourceHandle)
    {
        JsonService::seb_setJsonByHandle(handle, sourceHandle);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setJson(const std::string_view rawJson)
    {
        JsonService::seb_setJsonByParseable(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setProperty(const std::string_view key, const std::string_view rawJson)
    {
        JsonService::seb_setProperty(handle, key, rawJson);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setType(const IJsonServiceTypes::JsonType type)
    {
        JsonService::seb_setType(handle, type);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setEnum(const std::string_view rawJson)
    {
        JsonService::seb_setEnum(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setTypedArray(const IJsonServiceTypes::JsonType type)
    {
        JsonService::seb_setTypedArray(handle, type);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setEnumArray(const std::string_view rawJson)
    {
        JsonService::seb_setEnumArray(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setDefault(const std::string_view rawJson)
    {
        JsonService::seb_setDefault(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setMinimum(const std::string_view rawJson)
    {
        JsonService::seb_setMinimum(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setMaximum(const std::string_view rawJson)
    {
        JsonService::seb_setMaximum(handle, rawJson);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setDescription(const std::string_view value)
    {
        JsonService::seb_setDescription(handle, value);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setTitle(const std::string_view value)
    {
        JsonService::seb_setTitle(handle, value);
        return *this;
    }

    JsonSchemaElementBuilderWrapper& JsonSchemaElementBuilderWrapper::setReference(const std::string_view value)
    {
        JsonService::seb_setReference(handle, value);
        return *this;
    }

    // ====================================================================== //
    // JsonSchemaBuilder

    JsonSchemaBuilderWrapper::JsonSchemaBuilderWrapper(const std::string_view name) :
        handle(JsonService::instantiateSchemaBuilder(name)),
        selfManaged(true)
    {}

    JsonSchemaBuilderWrapper::JsonSchemaBuilderWrapper(const IJsonServiceTypes::JsonSchemaBuilderHandle handle) :
        handle(handle),
        selfManaged(false)
    {}

    JsonSchemaBuilderWrapper::~JsonSchemaBuilderWrapper()
    {
        if (selfManaged)
        {
            JsonService::freeSchemaBuilder(handle);
        }
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::setAdditionalProperties(const std::string_view rawJson)
    {
        JsonService::sb_setAdditionalProperties(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addRequired(const std::string_view requiredPropertyName)
    {
        JsonService::sb_addRequired(handle, requiredPropertyName);
        return *this;
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addAllOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addAllOfRequirement(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addAnyOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addAnyOfRequirement(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addOneOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addOneOfRequirement(handle, rawJson);
        return *this;
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addNoneOfRequirement(const std::string_view rawJson)
    {
        JsonService::sb_addNoneOfRequirement(handle, rawJson);
        return *this;
    }

    IJsonServiceTypes::ModifiableJsonHandle JsonSchemaBuilderWrapper::addElement(const std::string_view name)
    {
        return JsonService::sb_addElementByName(handle, name);
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addElement(const std::string_view name, const std::string rawJson)
    {
        JsonService::sb_addElementByParseable(handle, name, rawJson);
        return *this;
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addReference(
        const std::string_view propertyName,
        const std::string_view schemaName,
        const IJsonServiceTypes::JsonType type,
        bool setDefaults
    )
    {
        JsonService::sb_addReferenceByName(handle, propertyName, schemaName, type, setDefaults);
        return *this;
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addReference(
        const std::string_view propertyName,
        const JsonSchemaBuilderWrapper& subSchema,
        const IJsonServiceTypes::JsonType type,
        bool setDefaults
    )
    {
        JsonService::sb_addReferenceByType(handle, propertyName, subSchema.handle, type, setDefaults);
        return *this;
    }

    JsonSchemaBuilderWrapper JsonSchemaBuilderWrapper::addSubSchema(const std::string_view name)
    {
        return JsonSchemaBuilderWrapper(
                   JsonService::sb_addSubSchemaByName(handle, name)
               );
    }

    JsonSchemaBuilderWrapper& JsonSchemaBuilderWrapper::addSubSchema(const JsonSchemaBuilderWrapper& subSchema)
    {
        JsonService::sb_addSubSchemaByType(handle, subSchema.handle);
        return *this;
    }

    JsonSchemaElementBuilderWrapper JsonSchemaBuilderWrapper::addProperty(const std::string_view name)
    {
        return JsonSchemaElementBuilderWrapper(
                   JsonService::sb_addPropertyByName(handle, name)
               );
    }

    JsonSchemaElementBuilderWrapper JsonSchemaBuilderWrapper::addProperty(const std::string_view name, IJsonServiceTypes::JsonType type)
    {
        return JsonSchemaElementBuilderWrapper(
                   JsonService::sb_addPropertyByNameWithType(handle, name, type)
               );
    }

    IJsonServiceTypes::JsonHandle JsonSchemaBuilderWrapper::buildAndAdd(const IJsonServiceTypes::JsonTag tag) const
    {
        return JsonService::sb_buildAndAdd(handle, tag);
    }

} // namespace FileService
