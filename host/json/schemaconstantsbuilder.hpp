#ifndef SCHEMACONSTANTSBUILDER_HPP
#define SCHEMACONSTANTSBUILDER_HPP

#include <string>
#include <vector>

namespace JsonSchemaBuilderUtils
{
    std::string quoted(const std::string& arg);

    std::string indentString(int n);

    std::string keyToValue(const std::string& key, const std::string& value, int indent = 1);

    std::string makeSubschemaRef(const std::string& propertyName, const std::string& description, int indent = 1);

    using dict_t = std::initializer_list<std::pair<const std::string, const std::string>>;
    std::string block(const std::string& title, const dict_t& data, int indent = 1);

    using named_dict_t = std::initializer_list<std::pair<const std::string, const dict_t>>;
    std::string makeSubSchemaDef(const std::string& propertyName,
                                 const named_dict_t elements,
                                 const std::initializer_list<std::string> required = {},
                                 bool additionalProperties = false,
                                 int indent = 2);
}

class JsonBlockBuilder
{
    public:
        using KeyValuePair_t = std::pair<const std::string, const std::string>;

    private:
        const std::string title;
        std::vector<KeyValuePair_t> pairs;

    public:
        JsonBlockBuilder(const std::string& title);
        JsonBlockBuilder& add(const std::string& key, const std::string& value);

        std::string build(int indent = 1) const;
};

class JsonSchemaRefBuilder
{
    private:
        const std::string name;
        const std::string description;

    public:
        JsonSchemaRefBuilder(const std::string& name, const std::string& description);

        JsonBlockBuilder toBlockBuilder() const;
        std::string build(int indent = 1) const;
};

class JsonSubSchemaBuilder
{
    private:
        std::string name;
        std::vector<JsonBlockBuilder> elements;
        std::vector<std::string> required;
        bool additionalProperties = false;

    public:
        JsonSubSchemaBuilder(const std::string& name, bool additionalProperties = false);

        JsonBlockBuilder& addElement(const std::string& title);
        JsonSubSchemaBuilder& addReference(const std::string& name, const std::string& description);
        JsonSubSchemaBuilder& setRequired(const std::initializer_list<std::string>& requirements);

        std::string build(int indent = 2) const;
};

class JsonSchemaBuilder
{
    private:
        std::string name;
        std::vector<JsonBlockBuilder> elements;
        std::vector<JsonSubSchemaBuilder> subschemas;
        bool additionalProperties = false;

    public:
        JsonSchemaBuilder(const std::string& name, bool additionalProperties = false);

        JsonSubSchemaBuilder& addReference(const std::string& name, const std::string& description);

        std::string build(int indent = 2) const;
};

#endif // SCHEMACONSTANTSBUILDER_HPP

