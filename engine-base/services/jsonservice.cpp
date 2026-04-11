#include "services.hpp"
#include "jsonservice.hpp"
#include "memoryservice.hpp"

namespace JsonService
{
    // ====================================================================== //
    // Database

    const IJsonServiceTypes::EntryState getState(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.getState(tag);
    }

    const IJsonServiceTypes::JsonHandle get(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.get(tag);
    }

    const IJsonServiceTypes::JsonHandle getOrAdd(
        const IJsonServiceTypes::JsonTag tag,
        const void (* const creator)(const IJsonServiceTypes::ModifiableJsonHandle)
    )
    {
        return jsonService().database.getOrAdd(tag, creator);
    }

    const IJsonServiceTypes::JsonHandle getOrParse(const IJsonServiceTypes::JsonTag tag, const std::string_view json)
    {
        return jsonService().database.getOrParse(tag, json.data());
    }

    const IJsonServiceTypes::ModifiableJsonHandle declare(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.declare(tag);
    }

    const IJsonServiceTypes::JsonHandle commit(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.commit(tag);
    }

    const IJsonServiceTypes::JsonHandle parseValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::string_view json,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        return jsonService().database.parseValidatePatchAndAdd(tag, json.data(), validationSchemaTag);
    }

    const IJsonServiceTypes::JsonHandle readValidatePatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::filesystem::__cxx11::path& file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    )
    {
        return jsonService().database.readValidatePatchAndAdd(tag, file.c_str(), validationSchemaTag);
    }

    // ====================================================================== //
    // Item Access

    const IJsonServiceTypes::JsonHandle navigateTo(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer)
    {
        return jsonService().itemAccess.navigateTo(handle, jsonPointer.data());
    }

    const bool contains(const IJsonServiceTypes::JsonHandle handle, const std::string_view elementName)
    {
        return jsonService().itemAccess.containts(handle, elementName.data());
    }
    const IJsonServiceTypes::JsonType getType(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getType(handle);
    }

    const bool isNull(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isNull(handle);
    }

    const bool isBoolean(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isBoolean(handle);
    }

    const bool isInteger(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isInteger(handle);
    }

    const bool isUnsigned(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isUnsigned(handle);
    }

    const bool isFloat(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isFloat(handle);
    }

    const bool isString(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isString(handle);
    }

    const bool isObject(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isObject(handle);
    }

    const bool isArray(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isArray(handle);
    }

    const bool getAsBool(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsBool(handle);
    }

    const int getAsInteger(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsInteger(handle);
    }

    const unsigned long long getAsUnsigned(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsUnsigned(handle);
    }

    const double getAsFloat(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsFloat(handle);
    }

    const std::string_view getAsString(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsString(handle);
    }

    const int getArraySize(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getArraySize(handle);
    }

    const IJsonServiceTypes::JsonHandle getArrayItem(const IJsonServiceTypes::JsonHandle handle, const int index)
    {
        return jsonService().itemAccess.getArrayItem(handle, index);
    }

    void setToNull(const IJsonServiceTypes::ModifiableJsonHandle handle)
    {
        return jsonService().itemAccess.setToNull(handle);
    }

    void setToBool(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value)
    {
        return jsonService().itemAccess.setToBool(handle, value);
    }

    void setToInteger(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value)
    {
        return jsonService().itemAccess.setToInteger(handle, value);
    }

    void setToUnsigned(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned int value)
    {
        return jsonService().itemAccess.setToUnsigned(handle, value);
    }

    void setToFloat(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value)
    {
        return jsonService().itemAccess.setToFloat(handle, value);
    }

    void setToString(const IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view value)
    {
        return jsonService().itemAccess.setToString(handle, value.data());
    }

    void setToHandle(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        return jsonService().itemAccess.setToHandle(handle, source);
    }

    void setToArray(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        return jsonService().itemAccess.setToArray(handle, source);
    }

    void setToObject(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        return jsonService().itemAccess.setToObject(handle, source);
    }

    void setToParseable(const IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view source)
    {
        return jsonService().itemAccess.setToParseable(handle, source.data());
    }

    MemoryService::MemoryBlock dump(const IJsonServiceTypes::JsonHandle handle, int indent)
    {
        return jsonService().itemAccess.dump(handle, indent);
    }

    // ====================================================================== //
    // Schema Builder

    // ---------------------------------------------------------------------- //
    // instantiate and free


    IJsonServiceTypes::JsonSchemaBuilderHandle instantiateSchemaBuilder(const std::string_view name)
    {
        return jsonService().schemaBuilder.instantiateSchemaBuilder(name.data());
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle instantiateSchemaElementBuilder(const std::string_view name)
    {
        return jsonService().schemaBuilder.instantiateSchemaElementBuilder(name.data());
    }
    void freeSchemaBuilder(IJsonServiceTypes::JsonSchemaBuilderHandle& handle)
    {
        return jsonService().schemaBuilder.freeSchemaBuilder(handle);
    }

    void freeSchemaElementBuilder(IJsonServiceTypes::JsonSchemaElementBuilderHandle& handle)
    {
        return jsonService().schemaBuilder.freeSchemaElementBuilder(handle);
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder

    void sb_setAdditionalProperties(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view additionalProperties)
    {
        return jsonService().schemaBuilder.sb_setAdditionalProperties(handle, additionalProperties.data());
    }

    void sb_addRequired(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view required)
    {
        return jsonService().schemaBuilder.sb_addRequired(handle, required.data());
    }

    void sb_addAllOfReference(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view schemaName)
    {
        return jsonService().schemaBuilder.sb_addAllOfReference(handle, schemaName.data());
    }

    void sb_addAnyOfReference(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view schemaName)
    {
        return jsonService().schemaBuilder.sb_addAnyOfReference(handle, schemaName.data());
    }

    void sb_addOneOfReference(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view schemaName)
    {
        return jsonService().schemaBuilder.sb_addOneOfReference(handle, schemaName.data());
    }

    void sb_addNotReference(IJsonServiceTypes::JsonSchemaBuilderHandle handle, const std::string_view schemaName)
    {
        return jsonService().schemaBuilder.sb_addNotReference(handle, schemaName.data());
    }

    IJsonServiceTypes::ModifiableJsonHandle sb_addElementByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name
    )
    {
        return jsonService().schemaBuilder.sb_addElementByName(handle, name.data());
    }

    void sb_addElementByParseable(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view name,
        const std::string_view rawJson
    )
    {
        return jsonService().schemaBuilder.sb_addElementByParseable(handle, name.data(), rawJson.data());
    }

    void sb_addReferenceByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view schemaName,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        return jsonService().schemaBuilder.sb_addReferenceByName(
                   handle,
                   propertyName.data(),
                   schemaName.data(),
                   propertyType,
                   setDefaults
               );
    }

    void sb_addReferenceByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema,
        const IJsonServiceTypes::JsonType propertyType,
        bool setDefaults
    )
    {
        return jsonService().schemaBuilder.sb_addReferenceByType(
                   handle,
                   propertyName.data(),
                   subSchema,
                   propertyType,
                   setDefaults
               );
    }

    IJsonServiceTypes::JsonSchemaBuilderHandle sb_addSubSchemaByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view schemaName
    )
    {
        return jsonService().schemaBuilder.sb_addSubSchemaByName(handle, schemaName.data());
    }

    void sb_addSubSchemaByType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonSchemaBuilderHandle subSchema
    )
    {
        return jsonService().schemaBuilder.sb_addSubSchemaByType(handle, subSchema);
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByName(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName
    )
    {
        return jsonService().schemaBuilder.sb_addPropertyByName(handle, propertyName.data());
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle sb_addPropertyByNameWithType(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const std::string_view propertyName,
        IJsonServiceTypes::JsonType propertyType
    )
    {
        return jsonService().schemaBuilder.sb_addPropertyByNameWithType(handle, propertyName.data(), propertyType);
    }

    IJsonServiceTypes::JsonHandle sb_buildAndAdd(
        IJsonServiceTypes::JsonSchemaBuilderHandle handle,
        const IJsonServiceTypes::JsonTag tag
    )
    {
        return jsonService().schemaBuilder.sb_buildAndAdd(handle, tag);
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaElementBuilder

    const std::string_view seb_getName(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        return jsonService().schemaBuilder.seb_getName(handle);
    }

    IJsonServiceTypes::ModifiableJsonHandle seb_getJson(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        return jsonService().schemaBuilder.seb_getJson(handle);
    }

    void seb_setJsonByHandle(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonHandle json)
    {
        return jsonService().schemaBuilder.seb_setJsonByHandle(handle, json);
    }

    void seb_setJsonByParseable(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setJsonByParseable(handle, rawJson.data());
    }

    void seb_setProperty(
        IJsonServiceTypes::JsonSchemaElementBuilderHandle handle,
        const std::string_view propertyName,
        const std::string_view rawJson
    )
    {
        return jsonService().schemaBuilder.seb_setProperty(handle, propertyName.data(), rawJson.data());
    }

    void seb_setType(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        return jsonService().schemaBuilder.seb_setType(handle, type);
    }

    void seb_setTypedArray(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const IJsonServiceTypes::JsonType type)
    {
        return jsonService().schemaBuilder.seb_setTypedArray(handle, type);
    }

    void seb_setEnum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setEnum(handle, rawJson.data());
    }

    void seb_setDescription(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view description)
    {
        return jsonService().schemaBuilder.seb_setDescription(handle, description.data());
    }

    void seb_setTitle(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view title)
    {
        return jsonService().schemaBuilder.seb_setDefault(handle, title.data());
    }

    void seb_setDefault(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setDefault(handle, rawJson.data());
    }

    void seb_setMinimum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setMinimum(handle, rawJson.data());
    }

    void seb_setMaximum(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle, const std::string_view rawJson)
    {
        return jsonService().schemaBuilder.seb_setMaximum(handle, rawJson.data());
    }
}





