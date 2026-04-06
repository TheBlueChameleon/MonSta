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

            JsonSchemaElementBuilder& addProperty(const std::string_view key, const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& addType(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& addTypedArray(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& addEnum(const std::list<nlohmann::ordered_json>& items);
            JsonSchemaElementBuilder& addDescription(const std::string_view value);
            JsonSchemaElementBuilder& addTitle(const std::string_view value);
            JsonSchemaElementBuilder& addDefault(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& addMinimum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& addMaximum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& addReference(const std::string_view value);
    };

    class JsonSubSchemaBuilder
    {
        private:
            std::string                         name;
            nlohmann::ordered_json              additionalProperties = false;
            std::list<std::string>              required;
            std::list<JsonSchemaElementBuilder> elements;

        public:
            JsonSubSchemaBuilder(const std::string_view name);

            const std::string_view                      getName() const;
            const std::list<JsonSchemaElementBuilder>&  getElements() const;

            JsonSubSchemaBuilder& setAdditionalProperties(const nlohmann::ordered_json& additionalProperties);
            JsonSubSchemaBuilder& setRequired(const std::list<std::string>& required);

            JsonSchemaElementBuilder& addProperty(const std::string_view name);
            JsonSchemaElementBuilder& addProperty(const std::string_view name, IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& addReference(const std::string_view name);
            JsonSubSchemaBuilder&     addReference(
                const std::string_view name,
                const JsonSubSchemaBuilder& subSchema,
                const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
                bool setDefaults = true
            );

            nlohmann::ordered_json build() const;
    };

    class JsonSchemaBuilder
    {
        private:
            nlohmann::ordered_json              additionalProperties = false;
            std::list<std::string>              required;
            std::list<JsonSchemaElementBuilder> elements;
            std::list<JsonSubSchemaBuilder>     subSchemas;

        public:
            JsonSchemaBuilder() = default;

            JsonSchemaBuilder& setAdditionalProperties(const nlohmann::ordered_json& additionalProperties);
            JsonSchemaBuilder& setRequired(const std::list<std::string>& required);

            JsonSchemaBuilder&          addReference(const std::string_view name);
            JsonSchemaBuilder&          addReference(
                const std::string_view name,
                const JsonSubSchemaBuilder& subSchema,
                const IJsonServiceTypes::JsonType type = IJsonServiceTypes::JsonType::OBJECT,
                bool setDefaults = true
            );
            JsonSubSchemaBuilder&       addSubSchema(const std::string_view name);
            JsonSchemaBuilder&          addSubSchema(const JsonSubSchemaBuilder& subSchema);
            JsonSchemaBuilder&          addSubSchema(JsonSubSchemaBuilder&& subSchema);
            JsonSchemaElementBuilder&   addProperty(const std::string_view name);
            JsonSchemaElementBuilder&   addProperty(const std::string_view name, IJsonServiceTypes::JsonType type);

            nlohmann::ordered_json build() const;
    };
} // namespace JsonService

#endif // JSONSCHEMABUILDER_H
