#ifndef SCHEMACONSTANTSBUILDER_HPP
#define SCHEMACONSTANTSBUILDER_HPP

#include <sstream>

namespace JsonSchemaBuilder
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

#endif // SCHEMACONSTANTSBUILDER_HPP
