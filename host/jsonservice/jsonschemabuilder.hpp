#ifndef JSONSCHEMABUILDER_H
#define JSONSCHEMABUILDER_H

#include <list>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

#include <services/JsonService/IJsonService_Types.hpp>

namespace JsonService
{
    class JsonSchemaElementBuilder
    {
        private:
            const std::string name;
            nlohmann::ordered_json json;

        public:
            JsonSchemaElementBuilder();
            JsonSchemaElementBuilder(const std::string_view name);

            nlohmann::ordered_json& getJson();
            const nlohmann::ordered_json& getJson() const;
            const std::string_view getName() const;

            JsonSchemaElementBuilder& setProperty(const std::string_view key, const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setType(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& setTypedArray(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& setEnum(const std::list<nlohmann::ordered_json>& items);
            JsonSchemaElementBuilder& setDescription(const std::string_view value);
            JsonSchemaElementBuilder& setTitle(const std::string_view value);
            JsonSchemaElementBuilder& setDefault(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setMinimum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setMaximum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setReference(const std::string_view value);
    };

    class JsonSchemaBuilder
    {
        private:
            std::string                         name;
            nlohmann::ordered_json              additionalProperties = false;
            std::list<std::string>              required;
            std::list<JsonSchemaElementBuilder> elements;
            std::list<JsonSchemaBuilder>        subSchemas;

        public:
            JsonSchemaBuilder();
            JsonSchemaBuilder(const std::string_view name);

            const std::string_view                      getName() const;
            const std::list<JsonSchemaElementBuilder>&  getElements() const;

            JsonSchemaBuilder& setAdditionalProperties(const nlohmann::ordered_json& additionalProperties);
            JsonSchemaBuilder& setRequired(const std::list<std::string>& required);
            JsonSchemaBuilder& addRequired(const std::string_view required);

            nlohmann::ordered_json& addElement(const std::string_view name);

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

            JsonSchemaBuilder&          addSubSchema(const std::string_view name);
            JsonSchemaBuilder&          addSubSchema(const JsonSchemaBuilder& subSchema);
            JsonSchemaBuilder&          addSubSchema(JsonSchemaBuilder&& subSchema);

            JsonSchemaElementBuilder&   addProperty(const std::string_view name);
            JsonSchemaElementBuilder&   addProperty(const std::string_view name, IJsonServiceTypes::JsonType type);

            nlohmann::ordered_json build(bool includeSchemaReference = true) const;
    };
} // namespace JsonService

#endif // JSONSCHEMABUILDER_H
