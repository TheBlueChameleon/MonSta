#ifndef JSONSCHEMABUILDER_H
#define JSONSCHEMABUILDER_H

#include <list>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

namespace JsonService
{
    enum class JsonType {VOID, BOOLEAN, INTEGER, NUMBER, STRING, ARRAY, OBJECT};

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
            JsonSchemaElementBuilder& setType(const JsonType type);
            JsonSchemaElementBuilder& setArrayOfType(const JsonType type);
            JsonSchemaElementBuilder& setDescription(const std::string_view value);
            JsonSchemaElementBuilder& setTitle(const std::string_view value);
            JsonSchemaElementBuilder& setDefault(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setMinimum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setMaximum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setReference(const std::string_view value);
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
            JsonSchemaElementBuilder& addProperty(const std::string_view name, JsonType type);
            JsonSubSchemaBuilder&     addReference(const std::string_view name);
            JsonSubSchemaBuilder&     addReference(
                const std::string_view name,
                const JsonSubSchemaBuilder& subSchema,
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
                bool setDefaults = true
            );
            JsonSchemaBuilder&          addSubSchema(const JsonSubSchemaBuilder& subSchema);
            JsonSchemaBuilder&          addSubSchema(JsonSubSchemaBuilder&& subSchema);
            JsonSubSchemaBuilder&       addSubSchema(const std::string_view name);
            JsonSchemaElementBuilder&   addProperty(const std::string_view name);
            JsonSchemaElementBuilder&   addProperty(const std::string_view name, JsonType type);

            nlohmann::ordered_json build() const;
    };
} // namespace JsonService

#endif // JSONSCHEMABUILDER_H
