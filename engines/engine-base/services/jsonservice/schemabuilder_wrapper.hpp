#ifndef SCHEMABUILDER_WRAPPER_HPP
#define SCHEMABUILDER_WRAPPER_HPP

#include <string_view>

#include <services/JsonService/IJsonService_Types.hpp>

namespace JsonService
{
    class JsonSchemaElementBuilderWrapper
    {
        private:
            IJsonServiceTypes::JsonSchemaElementBuilderHandle handle;
            const bool selfManaged;

        public:
            JsonSchemaElementBuilderWrapper(const std::string_view name);
            JsonSchemaElementBuilderWrapper(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);
            ~JsonSchemaElementBuilderWrapper();

            const std::string_view getName() const;
            const IJsonServiceTypes::JsonHandle getJson() const;
            JsonSchemaElementBuilderWrapper& setJson(const IJsonServiceTypes::JsonHandle sourceHandle);
            JsonSchemaElementBuilderWrapper& setJson(const std::string_view rawJson);

            JsonSchemaElementBuilderWrapper& setProperty(const std::string_view key, const std::string_view rawJson);
            JsonSchemaElementBuilderWrapper& setType(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilderWrapper& setEnum(const std::string_view rawJson);
            JsonSchemaElementBuilderWrapper& setTypedArray(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilderWrapper& setEnumArray(const std::string_view rawJson);
            JsonSchemaElementBuilderWrapper& setDefault(const std::string_view rawJson);
            JsonSchemaElementBuilderWrapper& setMinimum(const std::string_view rawJson);
            JsonSchemaElementBuilderWrapper& setMaximum(const std::string_view rawJson);
            JsonSchemaElementBuilderWrapper& setDescription(const std::string_view value);
            JsonSchemaElementBuilderWrapper& setTitle(const std::string_view value);
            JsonSchemaElementBuilderWrapper& setReference(const std::string_view value);
    };

    class JsonSchemaBuilderWrapper
    {
        private:
            IJsonServiceTypes::JsonSchemaBuilderHandle handle;
            const bool selfManaged;

        public:
            JsonSchemaBuilderWrapper(const std::string_view name);
            JsonSchemaBuilderWrapper(const IJsonServiceTypes::JsonSchemaBuilderHandle handle);
            ~JsonSchemaBuilderWrapper();

            JsonSchemaBuilderWrapper& setAdditionalProperties(const std::string_view rawJson);

            JsonSchemaBuilderWrapper& addRequired(const std::string_view requiredPropertyName);
            JsonSchemaBuilderWrapper& addAllOfRequirement(const std::string_view rawJson);
            JsonSchemaBuilderWrapper& addAnyOfRequirement(const std::string_view rawJson);
            JsonSchemaBuilderWrapper& addOneOfRequirement(const std::string_view rawJson);
            JsonSchemaBuilderWrapper& addNoneOfRequirement(const std::string_view rawJson);

            IJsonServiceTypes::ModifiableJsonHandle addElement(const std::string_view name);
            JsonSchemaBuilderWrapper& addElement(const std::string_view name, const std::string rawJson);

            JsonSchemaBuilderWrapper& addReference(
                const std::string_view propertyName,
                const std::string_view schemaName,
                const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
                bool setDefaults = true
            );
            JsonSchemaBuilderWrapper& addReference(
                const std::string_view propertyName,
                const JsonSchemaBuilderWrapper& subSchema,
                const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
                bool setDefaults = true
            );

            JsonSchemaBuilderWrapper    addSubSchema(const std::string_view name);
            JsonSchemaBuilderWrapper&   addSubSchema(const JsonSchemaBuilderWrapper& subSchema);

            JsonSchemaElementBuilderWrapper    addProperty(const std::string_view name);
            JsonSchemaElementBuilderWrapper    addProperty(const std::string_view name, IJsonServiceTypes::JsonType type);

            IJsonServiceTypes::JsonHandle buildAndAdd(const IJsonServiceTypes::JsonTag tag) const;
    };

} // namespace JsonService

#endif // SCHEMABUILDER_WRAPPER_HPP
