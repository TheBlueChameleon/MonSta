#include <iostream>

#include <string>
using namespace std::string_literals;

#include "errorservice/errors.hpp"

#include "jsonschemabuilder.hpp"

using namespace nlohmann;

namespace JsonService
{
    // ====================================================================== //
    // shared auto build defaults code

    static ordered_json getDefault(const JsonSchemaElementBuilder& elementBuilder)
    {
        const auto& data = elementBuilder.getJson();
        auto it = data.find("default");
        if (it == data.end())
        {
            return ordered_json();
        }

        return *it;
    }

    static ordered_json getDefaults(const JsonSubSchemaBuilder& subSchemaBuilder)
    {
        auto result = ordered_json();

        for (const auto& element : subSchemaBuilder.getElements())
        {
            const auto elementDefault = getDefault(element);
            if (!elementDefault.is_null())
            {
                result[element.getName()] = elementDefault;
            }
        }

        return result;
    }

    // ====================================================================== //
    // JsonSchemaElementBuilder

    JsonSchemaElementBuilder::JsonSchemaElementBuilder() :
        JsonSchemaElementBuilder("")
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

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addProperty(const std::string_view key, const ordered_json& value)
    {
        json[key] = value;
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addType(const JsonType type)
    {
        switch (type)
        {
            case JsonType::ANY:
                return *this;
            case JsonType::VOID:
                return addProperty("type", "null");
            case JsonType::BOOLEAN:
                return addProperty("type", "boolean");
            case JsonType::INTEGER:
                return addProperty("type", "integer");
            case JsonType::NUMBER:
                return addProperty("type", "number");
            case JsonType::STRING:
                return addProperty("type", "string");
            case JsonType::ARRAY:
                return addProperty("type", "array");
            case JsonType::OBJECT:
                return addProperty("type", "object");
        }

        throw IllegalHostStateException("Unknown Json data type: "s + std::to_string(static_cast<int>(type)));
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addTypedArray(const JsonType type)
    {
        return addType(JsonType::ARRAY)
               .addProperty("items",
                            JsonSchemaElementBuilder().addType(type).getJson()
                           );
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addEnum(const std::list<nlohmann::ordered_json>& items)
    {
        return addProperty("enum", items);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addDescription(const std::string_view value)
    {
        return addProperty("description", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addTitle(const std::string_view value)
    {
        return addProperty("title", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addDefault(const ordered_json& value)
    {
        return addProperty("default", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addMinimum(const ordered_json& value)
    {
        return addProperty("minimum", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addMaximum(const ordered_json& value)
    {
        return addProperty("maximum", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::addReference(const std::string_view value)
    {
        return addProperty("$ref",  "#/$defs/"s + value.data());
    }

    // ====================================================================== //
    // JsonSubSchemaBuilder

    const std::string_view JsonSubSchemaBuilder::getName() const
    {
        return name;
    }

    const std::list<JsonSchemaElementBuilder>& JsonSubSchemaBuilder::getElements() const
    {
        return elements;
    }

    JsonSubSchemaBuilder::JsonSubSchemaBuilder(const std::string_view name) :
        name(name)
    {}

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::setAdditionalProperties(const ordered_json& additionalProperties)
    {
        this->additionalProperties = additionalProperties;
        return *this;
    }

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::setRequired(const std::list<std::string>& required)
    {
        this->required = required;
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
        elements.back().addType(type);
        return elements.back();
    }

    JsonSchemaElementBuilder& JsonSubSchemaBuilder::addReference(const std::string_view name)
    {
        elements.emplace_back(name);
        elements.back().addReference(name);
        return elements.back();
    }

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::addReference(
        const std::string_view name,
        const JsonSubSchemaBuilder& subSchema, const JsonType type,
        bool setDefaults
    )
    {
        elements.emplace_back(name);
        elements.back().addReference(name);
        elements.back().addType(type);
        if (setDefaults)
        {
            const auto defaults = getDefaults(subSchema);
            if (!defaults.is_null())
            {
                elements.back().addDefault(defaults);
            }
        }
        return *this;
    }

    ordered_json JsonSubSchemaBuilder::build() const
    {
        ordered_json result = json::object();

        if (!elements.empty())
        {
            auto& properties = result["properties"] = ordered_json::object();
            for (const auto& element : elements)
            {
                properties[element.getName()] = element.getJson();
            }
        }

        if (!required.empty())
        {
            result["required"] = required;
        }

        result["additionalProperties"] = additionalProperties;

        return result;
    }

    // ====================================================================== //
    // JsonSchemaBuilder

    JsonSchemaBuilder& JsonSchemaBuilder::setAdditionalProperties(const nlohmann::ordered_json& additionalProperties)
    {
        this->additionalProperties = additionalProperties;
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::setRequired(const std::list<std::string>& required)
    {
        this->required = required;
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addReference(const std::string_view name)
    {
        elements.emplace_back(name);
        elements.back().addReference(name);
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addReference(
        const std::string_view name,
        const JsonSubSchemaBuilder& subSchema,
        const JsonType type,
        bool setDefaults
    )
    {
        subSchemas.push_back(subSchema);

        elements.emplace_back(name);
        elements.back().addReference(subSchema.getName());
        elements.back().addType(type);
        if (setDefaults)
        {
            const auto defaults = getDefaults(subSchema);
            if (!defaults.is_null())
            {
                elements.back().addDefault(defaults);
            }
        }
        return *this;
    }

    JsonSubSchemaBuilder& JsonSchemaBuilder::addSubSchema(const std::string_view name)
    {
        subSchemas.emplace_back(name);
        return subSchemas.back();
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

    JsonSchemaElementBuilder& JsonSchemaBuilder::addProperty(const std::string_view name)
    {
        elements.emplace_back(name);
        return elements.back();
    }

    JsonSchemaElementBuilder& JsonSchemaBuilder::addProperty(const std::string_view name, JsonType type)
    {
        elements.emplace_back(name);
        elements.back().addType(type);
        return elements.back();
    }

    ordered_json JsonSchemaBuilder::build() const
    {
        ordered_json result =
        {
            {"$schema", "http://json-schema.org/draft-07/schema#"}
        };

        if (!elements.empty())
        {
            auto& properties = result["properties"] = ordered_json::object();
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

        result["additionalProperties"] = additionalProperties;

        return result;
    }
} // namespace JsonService
