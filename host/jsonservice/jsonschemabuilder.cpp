#include <string>
using namespace std::string_literals;

#include "errors.hpp"

#include "jsonschemabuilder.hpp"

using namespace nlohmann;

namespace JsonService
{
    // ====================================================================== //
    // JsonSchemaElementBuilder

    JsonSchemaElementBuilder::JsonSchemaElementBuilder() :
        name(""),
        json(json::object())
    {}

    JsonSchemaElementBuilder::JsonSchemaElementBuilder(const std::string_view name) :
        name(name),
        json(json::object())
    {}

    nlohmann::ordered_json& JsonSchemaElementBuilder::getJson()
    {
        return json;
    }

    const ordered_json& JsonSchemaElementBuilder::getJson() const
    {
        return json;
    }

    const std::string_view JsonSchemaElementBuilder::getName() const
    {
        return name;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setProperty(const std::string_view key, const nlohmann::json& value)
    {
        json[key] = value;
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setType(const JsonType type)
    {
        switch (type)
        {
            case JsonType::VOID:
                return setProperty("type", "null");
            case JsonType::BOOLEAN:
                return setProperty("type", "boolean");
            case JsonType::INTEGER:
                return setProperty("type", "integer");
            case JsonType::NUMBER:
                return setProperty("type", "number");
            case JsonType::STRING:
                return setProperty("type", "string");
            case JsonType::ARRAY:
                return setProperty("type", "array");
            case JsonType::OBJECT:
                return setProperty("type", "object");
        }

        throw IllegalStateException("Unknown Json data type: "s + std::to_string(static_cast<int>(type)));
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setArrayOfType(const JsonType type)
    {
        json["type"] = "array";
        json["items"] = JsonSchemaElementBuilder().setType(type).getJson();
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDescription(const std::string_view value)
    {
        return setProperty("description", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setTitle(const std::string_view value)
    {
        return setProperty("title", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDefault(const nlohmann::json& value)
    {
        return setProperty("default", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setMinimum(const nlohmann::json& value)
    {
        return setProperty("minimum", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setMaximum(const nlohmann::json& value)
    {
        return setProperty("maximum", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setReference(const std::string_view value)
    {
        return setProperty("$ref",  "#/$defs/"s + value.data());
    }

    // ====================================================================== //
    // JsonSubSchemaBuilder

    std::string JsonSubSchemaBuilder::getName() const
    {
        return name;
    }

    JsonSubSchemaBuilder::JsonSubSchemaBuilder(const std::string_view name) :
        name(name)
    {}

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::setAdditionalProperties(bool additionalProperties)
    {
        this->additionalProperties = additionalProperties;
        return *this;
    }

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::setRequired(const std::initializer_list<std::string>& required)
    {
        this->required = required;
        return *this;
    }

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::addReference(const std::string_view name, const std::string_view description)
    {
        elements.emplace_back(name);
        elements.back().setReference(name);
        return *this;
    }

    JsonSchemaElementBuilder& JsonSubSchemaBuilder::addProperty(const std::string_view name)
    {
        elements.emplace_back(name);
        return elements.back();
    }

    JsonSchemaElementBuilder& JsonSubSchemaBuilder::addProperty(const std::string_view name, JsonType type)
    {
        elements.emplace_back(name);
        elements.back().setType(type);
        return elements.back();
    }

    ordered_json JsonSubSchemaBuilder::build() const
    {
        ordered_json result = {{"additionalProperties", additionalProperties}};

        if (!required.empty())
        {
            result["required"] = required;
        }

        if (!elements.empty())
        {
            for (const auto& element : elements)
            {
                result[element.getName()] = element.getJson();
            }
        }

        return result;
    }

    // ====================================================================== //
    // JsonSchemaBuilder

    JsonSchemaBuilder& JsonSchemaBuilder::setAdditionalProperties(bool additionalProperties)
    {
        this->additionalProperties = additionalProperties;
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::setRequired(const std::initializer_list<std::string>& required)
    {
        this->required = required;
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addReference(const std::string_view name, const std::string_view description)
    {
        elements.emplace_back(name);
        elements.back().setReference(name);
        if (!description.empty())
        {
            elements.back().setDescription(description);
        }
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addSubSchema(const JsonSubSchemaBuilder& subSchema)
    {
        subSchemas.push_back(subSchema);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addSubSchema(JsonSubSchemaBuilder&& subSchema)
    {
        subSchemas.emplace_back(std::move(subSchema));
        return *this;
    }

    JsonSubSchemaBuilder& JsonSchemaBuilder::addSubSchema(const std::string_view name)
    {
        subSchemas.emplace_back(name);
        return subSchemas.back();
    }

    JsonSchemaElementBuilder& JsonSchemaBuilder::addProperty(const std::string_view name)
    {
        elements.emplace_back(name);
        return elements.back();
    }

    JsonSchemaElementBuilder& JsonSchemaBuilder::addProperty(const std::string_view name, JsonType type)
    {
        elements.emplace_back(name);
        elements.back().setType(type);
        return elements.back();
    }

    ordered_json JsonSchemaBuilder::build() const
    {
        ordered_json result =
        {
            {"$schema", "http://json-schema.org/draft-07/schema#"},
            {"additionalProperties", additionalProperties}
        };

        if (!elements.empty())
        {
            auto& properties = result["properties"] = json::object();
            for (const auto& element : elements)
            {
                properties[element.getName()] = element.getJson();
            }
        }

        if (!required.empty())
        {
            result["required"] = required;
        }

        if (!subSchemas.empty())
        {
            auto& defs = result["$defs"] = json::object();
            for (const auto& def : subSchemas)
            {
                defs[def.getName()] = def.build();
            }
        }

        return result;
    }

    // }
} // namespace JsonService
