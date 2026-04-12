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

            JsonSchemaBuilder& addRequired(const std::string_view required);
            JsonSchemaBuilder& addAllOfReference(const std::string_view schemaName);
            JsonSchemaBuilder& addAnyOfReference(const std::string_view schemaName);
            JsonSchemaBuilder& addOneOfReference(const std::string_view schemaName);
            JsonSchemaBuilder& addNotReference(const std::string_view schemaName);

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

            IJsonServiceTypes::JsonHandle build(const IJsonServiceTypes::JsonTag tag) const;
    };

} // namespace JsonService

#endif // SCHEMABUILDER_WRAPPER_HPP
