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

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setProperty(const std::string_view key, const ordered_json& value)
    {
        json[key] = value;
        return *this;
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setType(const IJsonServiceTypes::JsonType type)
    {
        switch (type)
        {
            case IJsonServiceTypes::JsonType::VOID:
                return setProperty("type", "null");
            case IJsonServiceTypes::JsonType::OBJECT:
                return setProperty("type", "object");
            case IJsonServiceTypes::JsonType::ARRAY:
                return setProperty("type", "array");
            case IJsonServiceTypes::JsonType::STRING:
                return setProperty("type", "string");
            case IJsonServiceTypes::JsonType::BOOLEAN:
                return setProperty("type", "boolean");
            case IJsonServiceTypes::JsonType::INTEGER:
                return setProperty("type", "integer");
            case IJsonServiceTypes::JsonType::UNSIGNED:
                return setProperty("type", "unsigned");
            case IJsonServiceTypes::JsonType::FLOAT:
                return setProperty("type", "number");
            case IJsonServiceTypes::JsonType::BINARY:
                return setProperty("type", "binary");
            case IJsonServiceTypes::JsonType::DISCARDED:
                // TODO: use this to erase type
                break;
        }

        throw IllegalHostStateException("Unknown Json data type: "s + std::to_string(static_cast<int>(type)));
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setTypedArray(const IJsonServiceTypes::JsonType type)
    {
        return setType(IJsonServiceTypes::JsonType::ARRAY)
               .setProperty("items",
                            JsonSchemaElementBuilder().setType(type).getJson()
                           );
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setEnum(const std::list<nlohmann::ordered_json>& items)
    {
        return setProperty("enum", items);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDescription(const std::string_view value)
    {
        return setProperty("description", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setTitle(const std::string_view value)
    {
        return setProperty("title", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setDefault(const ordered_json& value)
    {
        return setProperty("default", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setMinimum(const ordered_json& value)
    {
        return setProperty("minimum", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setMaximum(const ordered_json& value)
    {
        return setProperty("maximum", value);
    }

    JsonSchemaElementBuilder& JsonSchemaElementBuilder::setReference(const std::string_view value)
    {
        return setProperty("$ref",  "#/$defs/"s + value.data());
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

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::addRequired(const std::string_view required)
    {
        this->required.push_back(required.data());
        return *this;
    }

    JsonSchemaElementBuilder& JsonSubSchemaBuilder::addProperty(const std::string_view name)
    {
        elements.emplace_back(name);
        return elements.back();
    }

    JsonSchemaElementBuilder& JsonSubSchemaBuilder::addProperty(const std::string_view name, IJsonServiceTypes::JsonType type)
    {
        elements.emplace_back(name);
        elements.back().setType(type);
        return elements.back();
    }

    JsonSchemaElementBuilder& JsonSubSchemaBuilder::addReference(const std::string_view name)
    {
        elements.emplace_back(name);
        elements.back().setReference(name);
        return elements.back();
    }

    JsonSubSchemaBuilder& JsonSubSchemaBuilder::addReference(
        const std::string_view name,
        const JsonSubSchemaBuilder& subSchema, const IJsonServiceTypes::JsonType type,
        bool setDefaults
    )
    {
        elements.emplace_back(name);
        elements.back().setReference(name);
        elements.back().setType(type);
        if (setDefaults)
        {
            const auto defaults = getDefaults(subSchema);
            if (!defaults.is_null())
            {
                elements.back().setDefault(defaults);
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

    JsonSchemaBuilder& JsonSchemaBuilder::addRequired(const std::string_view required)
    {
        this->required.push_back(required.data());
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addReference(
        const std::string_view propertyName,
        const std::string_view schemaName,
        const IJsonServiceTypes::JsonType type,
        bool setDefaults
        )
    {
        elements.emplace_back(propertyName);
        elements.back().setReference(schemaName);
        elements.back().setType(type);
        if (setDefaults)
        {
            auto it = std::find_if(subSchemas.cbegin(), subSchemas.cend(),
                                   [&schemaName](const JsonSubSchemaBuilder& subSchema)
            {
                return subSchema.getName() == schemaName;
            }
                                  );
            if (it == subSchemas.cend())
            {
                throw JsonError("Unknown subschema: '"s + schemaName.data() + "'");
            }

            const auto defaults = getDefaults(*it);
            if (!defaults.is_null())
            {
                elements.back().setDefault(defaults);
            }
        }
        return *this;
    }

    JsonSchemaBuilder& JsonSchemaBuilder::addReference(
        const std::string_view propertyName,
        const JsonSubSchemaBuilder& subSchema,
        const IJsonServiceTypes::JsonType type,
        bool setDefaults
        )
    {
        subSchemas.push_back(subSchema);

        elements.emplace_back(propertyName);
        elements.back().setReference(subSchema.getName());
        elements.back().setType(type);
        if (setDefaults)
        {
            const auto defaults = getDefaults(subSchema);
            if (!defaults.is_null())
            {
                elements.back().setDefault(defaults);
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

    JsonSchemaElementBuilder& JsonSchemaBuilder::addProperty(const std::string_view name, IJsonServiceTypes::JsonType type)
    {
        elements.emplace_back(name);
        elements.back().setType(type);
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
