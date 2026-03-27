#include <sstream>
#include <string>
using namespace std::string_literals;

#include "schemaconstantsbuilder.hpp"

namespace JsonSchemaBuilderUtils
{
    std::string quoted(const std::string& arg)
    {
        return "\""s + arg + "\"";
    }

    std::string indentString(int n)
    {
        return std::string(n, '\t');
    }

    std::string keyToValue(const std::string& key, const std::string& value, int indent)
    {
        std::stringstream ss;

        ss << indentString(indent) << quoted(key) << " : " << value;

        return ss.str();
    }
}

// ========================================================================== //
// JsonBlockBuilder

using namespace JsonSchemaBuilderUtils;

JsonBlockBuilder::JsonBlockBuilder(const std::string& name) :
    name(name)
{}

JsonBlockBuilder& JsonBlockBuilder::addKeyValuePair(const std::string& key, const std::string& value)
{
    pairs.emplace_back(key, value);
    return *this;
}

JsonBlockBuilder& JsonBlockBuilder::addDefault(const std::string& value)
{
    return addKeyValuePair("default", value);
}

JsonBlockBuilder& JsonBlockBuilder::addType(const std::string& value)
{
    return addKeyValuePair("type", value);
}

JsonBlockBuilder& JsonBlockBuilder::addTitle(const std::string& value)
{
    return addKeyValuePair("title", value);
}

JsonBlockBuilder& JsonBlockBuilder::addDescription(const std::string& value)
{
    return addKeyValuePair("description", value);
}

std::string JsonBlockBuilder::build(int indent) const
{
    std::stringstream ss;

    ss << indentString(indent) << quoted(name) << " : {\n";
    int i = 0;
    int size = pairs.size();
    for (const auto& element : pairs)
    {
        ++i;
        ss << keyToValue(element.first, element.second, indent + 1);
        ss << (i < size ? "," : "") << std::endl;
    }
    ss << indentString(indent) << "}";

    return ss.str();
}

// ========================================================================== //
// JsonSchemaRefBuilder

JsonSchemaRefBuilder::JsonSchemaRefBuilder(const std::string& name, const std::string& description) :
    name(name), description(description)
{}

JsonBlockBuilder JsonSchemaRefBuilder::toBlockBuilder() const
{
    auto builder = JsonBlockBuilder(name);

    builder.addKeyValuePair("$ref", quoted("#/$defs/"s + name));
    if (!description.empty())
    {
        builder.addDescription(quoted(description));
    }

    return builder;
}

std::string JsonSchemaRefBuilder::build(int indent) const
{
    return toBlockBuilder().build(indent);
}

// ========================================================================== //
// JsonSubSchemaBuilder

JsonSubSchemaBuilder::JsonSubSchemaBuilder(const std::string& name, bool additionalProperties) :
    name(name), additionalProperties(additionalProperties)
{}

JsonSubSchemaBuilder& JsonSubSchemaBuilder::addReference(const std::string& name, const std::string& description)
{
    elements.push_back(
        JsonSchemaRefBuilder(name, description).toBlockBuilder()
    );
    return *this;
}

JsonBlockBuilder& JsonSubSchemaBuilder::addProperty(const std::string& title)
{
    elements.emplace_back(title);
    return elements.back();
}

JsonBlockBuilder& JsonSubSchemaBuilder::addProperty(const std::string& title, const std::string& type)
{
    elements.emplace_back(title);
    elements.back().addType(type);
    return elements.back();
}

JsonSubSchemaBuilder& JsonSubSchemaBuilder::setRequired(const std::initializer_list<std::string>& requirements)
{
    required = requirements;
    return *this;
}

std::string JsonSubSchemaBuilder::build(int indent) const
{
    std::stringstream ss;

    ss << indentString(indent) << quoted(name) << " : {\n";
    ss << indentString(indent + 1) + quoted("properties") + " : {\n";

    int i = 0;
    int size = elements.size();
    for (const auto& element : elements)
    {
        ++i;
        ss << element.build(indent + 2);
        ss << (i < size ? "," : "") << std::endl;
    }
    ss << indentString(indent + 1) + "},\n";

    ss << indentString(indent + 1) << quoted("required") << " : [";
    i = 0;
    size = required.size();
    for (const auto& item: required)
    {
        ++i;
        ss << quoted(item) << (i < size ? ", " : "");
    }
    ss << "],\n";

    ss << keyToValue("additionalProperties", (additionalProperties ? "true" : "false"), indent + 1) << "\n";
    ss << indentString(indent) + "}";

    return ss.str();
}

// ========================================================================== //
// JsonSchemaBuilder

JsonSchemaBuilder::JsonSchemaBuilder(bool additionalProperties) :
    additionalProperties(additionalProperties)
{}

JsonBlockBuilder& JsonSchemaBuilder::addProperty(const std::string& title)
{
    elements.emplace_back(title);
    return elements.back();
}

JsonSchemaBuilder& JsonSchemaBuilder::addReference(const std::string& name, const std::string& description)
{
    elements.push_back(JsonSchemaRefBuilder(name, description).toBlockBuilder());
    return *this;
}

JsonSchemaBuilder& JsonSchemaBuilder::addSubSchema(const JsonSubSchemaBuilder& subSchema)
{
    subschemas.push_back(subSchema);
    return *this;
}

JsonSubSchemaBuilder& JsonSchemaBuilder::addSubSchema(const std::string& name, bool additionalProperties)
{
    subschemas.emplace_back(name, additionalProperties);
    return subschemas.back();
}

JsonSchemaBuilder& JsonSchemaBuilder::setRequired(const std::initializer_list<std::string>& requirements)
{
    required = requirements;
    return *this;
}

std::string JsonSchemaBuilder::build() const
{
    std::stringstream ss;

    ss << "{\n";

    ss << "\t" R"("$schema" : "http://json-schema.org/draft-07/schema#",)" "\n";

    ss << "\t" R"("properties" : {)" "\n";
    int i = 0;
    int size = elements.size();
    for (const auto& property : elements)
    {
        ++i;
        ss << property.build(2) << (i < size ? "," : "") << "\n";
    }
    ss << "\t},\n";

    ss << "\t" R"("required" : [)" ;
    i = 0;
    size = required.size();
    for (const auto& r : required)
    {
        ++i;
        ss << quoted(r) << (i < size ? ", " : "");
    }
    ss << "],\n";

    ss << keyToValue("additionalProperties", (additionalProperties ? "true" : "false"), 1) << ",\n";


    ss << "\t" R"("$defs" : {)" "\n";
    i = 0;
    size = subschemas.size();
    for (const auto& s : subschemas)
    {
        ++i;
        ss << s.build(2) << (i < size ? ", " : "") << "\n";
    }
    ss << "\t}\n";

    ss << "}\n";

    return ss.str();
}
