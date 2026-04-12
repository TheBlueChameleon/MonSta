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
            JsonSchemaElementBuilder(const std::string_view name, const nlohmann::ordered_json& json);

            const std::string_view getName() const;
            nlohmann::ordered_json& getJson();
            const nlohmann::ordered_json& getJson() const;
            JsonSchemaElementBuilder& setJson(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setJson(nlohmann::ordered_json&& value);

            JsonSchemaElementBuilder& setProperty(const std::string_view key, const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setType(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& setEnum(const nlohmann::ordered_json& items);
            JsonSchemaElementBuilder& setTypedArray(const IJsonServiceTypes::JsonType type);
            JsonSchemaElementBuilder& setEnumArray(const nlohmann::ordered_json& items);
            JsonSchemaElementBuilder& setDefault(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setMinimum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setMaximum(const nlohmann::ordered_json& value);
            JsonSchemaElementBuilder& setDescription(const std::string_view value);
            JsonSchemaElementBuilder& setTitle(const std::string_view value);
            JsonSchemaElementBuilder& setReference(const std::string_view value);
    };

    class JsonSchemaBuilder
    {
        private:
            std::string                         name;
            nlohmann::ordered_json              additionalProperties = false;
            std::list<std::string>              required;
            std::list<nlohmann::ordered_json>   allOfRequirements;
            std::list<nlohmann::ordered_json>   anyOfRequirements;
            std::list<nlohmann::ordered_json>   oneOfRequirements;
            std::list<nlohmann::ordered_json>   noneOfRequirements;
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

            JsonSchemaBuilder& setAllOfRequirements(const std::list<nlohmann::ordered_json>& requirements);
            JsonSchemaBuilder& addAllOfRequirements(const nlohmann::ordered_json& requirements);

            JsonSchemaBuilder& setAnyOfRequirements(const std::list<nlohmann::ordered_json>& requirements);
            JsonSchemaBuilder& addAnyOfRequirements(const nlohmann::ordered_json& requirements);

            JsonSchemaBuilder& setOneOfRequirements(const std::list<nlohmann::ordered_json>& requirements);
            JsonSchemaBuilder& addOneOfRequirements(const nlohmann::ordered_json& requirements);

            JsonSchemaBuilder& setNoneOfRequirements(const std::list<nlohmann::ordered_json>& requirements);
            JsonSchemaBuilder& addNoneOfRequirements(const nlohmann::ordered_json& requirements);

            nlohmann::ordered_json& addElement(const std::string_view name);
            JsonSchemaBuilder& addElement(const std::string_view name, const nlohmann::ordered_json& element);

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
