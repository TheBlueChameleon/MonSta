#include <string>
using namespace std::string_literals;

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

    nlohmann::json& JsonSchemaElementBuilder::getJson()
    {
        return json;
    }

    const json& JsonSchemaElementBuilder::getJson() const
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
                json["type"] = "null";
                break;
            case JsonType::BOOLEAN:
                json["type"] = "boolean";
                break;
            case JsonType::INTEGER:
                json["type"] = "integer";
                break;
            case JsonType::NUMBER:
                json["type"] = "number";
                break;
            case JsonType::STRING:
                json["type"] = "string";
                break;
            case JsonType::ARRAY:
                json["type"] = "array";
                break;
            case JsonType::OBJECT:
                json["type"] = "object";
                break;
        }

        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setArrayOfType(const JsonType type)
    {
        json["type"] = "array";
        json["items"] = JsonSchemaElementBuilder().setType(type).getJson();
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDescription(const std::string_view value)
    {
        json["description"] = value;
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setTitle(const std::string_view value)
    {
        json["title"] = value;
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDefault(const std::string_view value)
    {
        json["default"] = value;
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setReference(const std::string_view value)
    {
        json["$ref"] = "#/$defs/"s + value.data();
        return *this;
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

    json JsonSubSchemaBuilder::build() const
    {
        json result = {{"additionalProperties", additionalProperties}};

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

    json JsonSchemaBuilder::build() const
    {
        json result =
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
