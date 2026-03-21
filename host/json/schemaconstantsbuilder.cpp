#include <sstream>
#include <string>
using namespace std::string_literals;

#include "schemaconstantsbuilder.hpp"

namespace JsonSchemaBuilder
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

        // std::stringstream ss;

        // ss << indentString(indent) << quoted(propertyName) << ": {\n";
        // ss << keyToValue("$ref", "#/$defs/"s + propertyName, indent + 1);
        // ss << keyToValue("description", description, indent + 1);
        // ss << indentString(indent) << "}";

        // return ss.str();
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
