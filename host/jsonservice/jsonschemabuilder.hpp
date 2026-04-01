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
            nlohmann::json json;

        public:
            JsonSchemaElementBuilder();
            JsonSchemaElementBuilder(const std::string_view name);

            nlohmann::json& getJson();
            const nlohmann::json& getJson() const;
            const std::string_view getName() const;

            JsonSchemaElementBuilder& setProperty(const std::string_view key, const nlohmann::json& value);
            JsonSchemaElementBuilder& setType(const JsonType type);
            JsonSchemaElementBuilder& setArrayOfType(const JsonType type);
            JsonSchemaElementBuilder& setDescription(const std::string_view value);
            JsonSchemaElementBuilder& setTitle(const std::string_view value);
            JsonSchemaElementBuilder& setDefault(const nlohmann::json& value);
            JsonSchemaElementBuilder& setMinimum(const nlohmann::json& value);
            JsonSchemaElementBuilder& setMaximum(const nlohmann::json& value);
            JsonSchemaElementBuilder& setReference(const std::string_view value);
    };

    class JsonSubSchemaBuilder
    {
        private:
            std::string                         name;
            bool                                additionalProperties = false;
            std::list<std::string>              required;
            std::list<JsonSchemaElementBuilder> elements;

        public:
            JsonSubSchemaBuilder(const std::string_view name);

            std::string getName() const;

            JsonSubSchemaBuilder& setAdditionalProperties(bool additionalProperties);
            JsonSubSchemaBuilder& setRequired(const std::initializer_list<std::string>& required);

            JsonSubSchemaBuilder&     addReference(const std::string_view name, const std::string_view description = "");
            JsonSchemaElementBuilder& addProperty(const std::string_view name);
            JsonSchemaElementBuilder& addProperty(const std::string_view name, JsonType type);

            nlohmann::json build() const;
    };

    class JsonSchemaBuilder
    {
        private:
            bool additionalProperties = false;
            std::list<std::string>              required;
            std::list<JsonSchemaElementBuilder> elements;
            std::list<JsonSubSchemaBuilder>     subSchemas;

        public:
            JsonSchemaBuilder() = default;

            JsonSchemaBuilder& setAdditionalProperties(bool additionalProperties);
            JsonSchemaBuilder& setRequired(const std::initializer_list<std::string>& required);

            JsonSchemaBuilder&          addReference(const std::string_view name, const std::string_view description = "");
            JsonSchemaBuilder&          addSubSchema(const JsonSubSchemaBuilder& subSchema);
            JsonSchemaBuilder&          addSubSchema(JsonSubSchemaBuilder&& subSchema);
            JsonSubSchemaBuilder&       addSubSchema(const std::string_view name);
            JsonSchemaElementBuilder&   addProperty(const std::string_view name);
            JsonSchemaElementBuilder&   addProperty(const std::string_view name, JsonType type);

            nlohmann::json build() const;
    };
} // namespace JsonService

#endif // JSONSCHEMABUILDER_H
