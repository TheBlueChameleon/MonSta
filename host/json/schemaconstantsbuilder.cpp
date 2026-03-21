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

    using dict_t = std::initializer_list<std::pair<const std::string, const std::string>>;
    std::string block(const std::string& title, const dict_t& elements, int indent)
    {
        std::stringstream ss;

        ss << indentString(indent) << quoted(title) << " : {\n";
        int i = 0;
        int size = elements.size();
        for (const auto& element : elements)
        {
            ++i;
            ss << keyToValue(element.first, element.second, indent + 1);
            ss << (i < size ? "," : "") << std::endl;
        }
        ss << indentString(indent) << "}";

        return ss.str();
    }

    std::string makeSubschemaRef(const std::string& propertyName, const std::string& description, int indent)
    {
        return block(propertyName,
        {
            {"$ref", quoted("#/$defs/"s + propertyName)},
            {"description", quoted(description)}
        }, indent
                    );
    }

    std::string makeSubSchemaDef(
        const std::string& propertyName,
        const named_dict_t elements,
        const std::initializer_list<std::string> required,
        bool additionalProperties,
        int indent)
    {
        std::stringstream ss;

        ss << indentString(indent) << quoted(propertyName) << " : {\n";
        ss << indentString(indent + 1) + quoted("properties") + " : {\n";

        int i = 0;
        int size = elements.size();
        for (const auto& element : elements)
        {
            ++i;
            ss << block(element.first, element.second, indent + 2);
            ss << (i < size ? "," : "") << std::endl;
        }
        ss << indentString(indent + 1) + "},\n";

        ss << indentString(indent + 1) << quoted("required") << " : [";
        i = 0;
        size = required.size();
        for (const auto& item: required)
        {
            ++i;
            ss << quoted(item) << (i < size ? "," : "");
        }
        ss << "],\n";

        ss << keyToValue("additionalProperties", (additionalProperties ? "true" : "false"), indent + 1) << "\n";
        ss << indentString(indent) + "}";


        return ss.str();
    }

}

// ========================================================================== //
// JsonBlockBuilder

using namespace JsonSchemaBuilderUtils;

JsonBlockBuilder::JsonBlockBuilder(const std::string& title) :
    title(title)
{}

JsonBlockBuilder& JsonBlockBuilder::add(const std::string& key, const std::string& value)
{
    pairs.emplace_back(key, value);
    return *this;
}

std::string JsonBlockBuilder::build(int indent) const
{
    std::stringstream ss;

    ss << indentString(indent) << quoted(title) << " : {\n";
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

    builder.add("$ref", quoted("#/$defs/"s + name));
    builder.add("description", quoted(description));

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

JsonBlockBuilder& JsonSubSchemaBuilder::addElement(const std::string& title)
{
    elements.emplace_back(title);
    return elements.back();
}

JsonSubSchemaBuilder& JsonSubSchemaBuilder::addReference(const std::string& name, const std::string& description)
{
    elements.push_back(
        JsonSchemaRefBuilder(name, description).toBlockBuilder()
    );
    return *this;
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
        ss << quoted(item) << (i < size ? "," : "");
    }
    ss << "],\n";

    ss << keyToValue("additionalProperties", (additionalProperties ? "true" : "false"), indent + 1) << "\n";
    ss << indentString(indent) + "}";

    return ss.str();
}
