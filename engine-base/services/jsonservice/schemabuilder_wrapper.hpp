#ifndef SCHEMABUILDER_WRAPPER_HPP
#define SCHEMABUILDER_WRAPPER_HPP

#include <string_view>

#include <services/JsonService/IJsonService_Types.hpp>

namespace JsonService
{
    class JsonSchemaElementBuilder
    {
        private:
            IJsonServiceTypes::JsonSchemaElementBuilderHandle handle;
            const bool selfManaged;

        public:
            JsonSchemaElementBuilder(const std::string_view name);
            JsonSchemaElementBuilder(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);
            ~JsonSchemaElementBuilder();

            const std::string_view getName() const;
            const IJsonServiceTypes::JsonHandle getJson() const;
            JsonSchemaElementBuilder& setJson(const IJsonServiceTypes::JsonHandle sourceHandle);
            JsonSchemaElementBuilder& setJson(const std::string_view rawJson);

            JsonSchemaElementBuilder& setProperty(const std::string_view key, const std::string_view rawJson);
            JsonSchemaElementBuilder& setType(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& setTypedArray(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& setEnum(const std::string_view rawJson);
            JsonSchemaElementBuilder& setDescription(const std::string_view value);
            JsonSchemaElementBuilder& setTitle(const std::string_view value);
            JsonSchemaElementBuilder& setDefault(const std::string_view rawJson);
            JsonSchemaElementBuilder& setMinimum(const std::string_view rawJson);
            JsonSchemaElementBuilder& setMaximum(const std::string_view rawJson);
            JsonSchemaElementBuilder& setReference(const std::string_view value);
    };

    class JsonSchemaBuilder
    {
        private:
            IJsonServiceTypes::JsonSchemaBuilderHandle handle;
            const bool selfManaged;

        public:
            JsonSchemaBuilder(const std::string_view name);
            JsonSchemaBuilder(const IJsonServiceTypes::JsonSchemaBuilderHandle handle);
            ~JsonSchemaBuilder();

            JsonSchemaBuilder& setAdditionalProperties(const std::string_view rawJson);

            JsonSchemaBuilder& addRequired(const std::string_view requiredPropertyName);
            JsonSchemaBuilder& addAllOfRequirement(const std::string_view rawJson);
            JsonSchemaBuilder& addAnyOfRequirement(const std::string_view rawJson);
            JsonSchemaBuilder& addOneOfRequirement(const std::string_view rawJson);
            JsonSchemaBuilder& addNoneOfRequirement(const std::string_view rawJson);

            IJsonServiceTypes::ModifiableJsonHandle addElement(const std::string_view name);
            JsonSchemaBuilder& addElement(const std::string_view name, const std::string rawJson);

            JsonSchemaBuilder&          addReference(
                const std::string_view propertyName,
                const std::string_view schemaName,
                const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
                bool setDefaults = true
            );
            JsonSchemaBuilder&          addReference(
                const std::string_view propertyName,
                const JsonSchemaBuilder& subSchema,
                const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
                bool setDefaults = true
            );

            JsonSchemaBuilder           addSubSchema(const std::string_view name);
            JsonSchemaBuilder&          addSubSchema(const JsonSchemaBuilder& subSchema);

            JsonSchemaElementBuilder    addProperty(const std::string_view name);
            JsonSchemaElementBuilder    addProperty(const std::string_view name, IJsonServiceTypes::JsonType type);

            IJsonServiceTypes::JsonHandle buildAndAdd(const IJsonServiceTypes::JsonTag tag) const;
    };

} // namespace JsonService

#endif // SCHEMABUILDER_WRAPPER_HPP
