#ifndef SCHEMACONSTANTSBUILDER_HPP
#define SCHEMACONSTANTSBUILDER_HPP

#include <string>
#include <vector>

namespace JsonSchemaBuilderUtils
{
    std::string quoted(const std::string& arg);

    std::string indentString(int n);

    std::string keyToValue(const std::string& key, const std::string& value, int indent = 1);
}

class JsonBlockBuilder
{
    public:
        using KeyValuePair_t = std::pair<const std::string, const std::string>;

    private:
        const std::string name;
        std::vector<KeyValuePair_t> pairs;

    public:
        JsonBlockBuilder(const std::string& name);
        JsonBlockBuilder& addKeyValuePair(const std::string& key, const std::string& value);
        JsonBlockBuilder& addType(const std::string& value);
        JsonBlockBuilder& addTitle(const std::string& value);
        JsonBlockBuilder& addDescription(const std::string& value);

        std::string build(int indent = 0) const;
};

class JsonSchemaRefBuilder
{
    private:
        const std::string name;
        const std::string description;

    public:
        JsonSchemaRefBuilder(const std::string& name, const std::string& description = "");

        JsonBlockBuilder toBlockBuilder() const;
        std::string build(int indent = 0) const;
};

class JsonSubSchemaBuilder
{
    private:
        std::string name;
        bool additionalProperties = false;
        std::vector<JsonBlockBuilder> elements;
        std::vector<std::string> required;

    public:
        JsonSubSchemaBuilder(const std::string& name, bool additionalProperties = false);

        JsonSubSchemaBuilder& addReference(const std::string& name, const std::string& description = "");
        JsonBlockBuilder&     addProperty(const std::string& title);
        JsonBlockBuilder&     addProperty(const std::string& title, const std::string& type);

        JsonSubSchemaBuilder& setRequired(const std::initializer_list<std::string>& requirements);

        std::string build(int indent = 0) const;
};

class JsonSchemaBuilder
{
    private:
        bool additionalProperties = false;
        std::vector<JsonBlockBuilder> elements;
        std::vector<std::string> required;
        std::vector<JsonSubSchemaBuilder> subschemas;

    public:
        JsonSchemaBuilder(bool additionalProperties = false);

        JsonBlockBuilder&     addProperty(const std::string& title);
        JsonSchemaBuilder&    addReference(const std::string& name, const std::string& description = "");
        JsonSchemaBuilder&    addSubSchema(const JsonSubSchemaBuilder& subSchema);
        JsonSubSchemaBuilder& addSubSchema(const std::string& name, bool additionalProperties = false);

        JsonSchemaBuilder& setRequired(const std::initializer_list<std::string>& requirements);

        std::string build() const;
};

#endif // SCHEMACONSTANTSBUILDER_HPP

