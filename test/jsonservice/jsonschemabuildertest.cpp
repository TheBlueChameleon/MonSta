#include <string>

#include "jsonschemabuildertest.hpp"

#include "jsonservice/jsonschemabuilder.hpp"

using namespace JsonService;
using namespace nlohmann;

TEST_F(JsonSchemaBuilderTest, ElementBuilder_setProperty_InOrder)
{
    // setup
    auto builder = JsonSchemaElementBuilder();

    builder.addProperty("key", "value");
    builder.addProperty("number", 42);
    builder.addProperty("complex", json::parse("{}"));

    // when
    std::string result = builder.getJson().dump(2);
    std::string expected = R"({
  "key": "value",
  "number": 42,
  "complex": {}
})";

    // then
    EXPECT_EQ(result, expected);
}

TEST_F(JsonSchemaBuilderTest, SubSchemaBuilder_All_InOrder)
{
    // setup
    auto builder = JsonSubSchemaBuilder("ignored");

    builder.setRequired({"foo"});
    builder.setAdditionalProperties(json::object());

    builder.addProperty("property");
    builder.addProperty("typedProperty", JsonType::BOOLEAN);
    builder.addReference("ref");

    // when
    std::string result = builder.build().dump(2);
    std::string expected = R"({
  "properties": {
    "property": {},
    "typedProperty": {
      "type": "boolean"
    },
    "ref": {
      "$ref": "#/$defs/ref"
    }
  },
  "required": [
    "foo"
  ],
  "additionalProperties": {}
})";

    // then
    EXPECT_EQ(result, expected);
}

TEST_F(JsonSchemaBuilderTest, SubSchemaBuilder_AutoDefaults)
{
    // setup
    auto builder = JsonSubSchemaBuilder("ignored");

    builder.addProperty("empty");
    builder.addProperty("defaulted").addDefault("value");
    builder.addReference("recursive", builder);

    // when
    std::string result = builder.build().dump(2);
    std::string expected = R"({
  "properties": {
    "empty": {},
    "defaulted": {
      "default": "value"
    },
    "recursive": {
      "$ref": "#/$defs/recursive",
      "default": {
        "defaulted": "value"
      }
    }
  },
  "additionalProperties": false
})";

    // then
    EXPECT_EQ(result, expected);
}

TEST_F(JsonSchemaBuilderTest, SchemaBuilder_EmptyPreset)
{
    // setup
    auto builder = JsonSchemaBuilder();

    // when
    std::string result = builder.build().dump(2);
    std::string expected = R"({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "additionalProperties": false
})";

    // then
    EXPECT_EQ(result, expected);
}

TEST_F(JsonSchemaBuilderTest, SchemaBuilder_AutoDefaults)
{
    // setup
    auto subSchema = JsonSubSchemaBuilder("subSchema");
    subSchema.addProperty("prop").addDefault("default");

    auto builder = JsonSchemaBuilder();
    builder.addReference("property", subSchema);

    // when
    std::string result = builder.build().dump(2);
    std::string expected = R"({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "properties": {
    "property": {
      "$ref": "#/$defs/subSchema",
      "default": {
        "prop": "default"
      }
    }
  },
  "$defs": {
    "subSchema": {
      "properties": {
        "prop": {
          "default": "default"
        }
      },
      "additionalProperties": false
    }
  },
  "additionalProperties": false
})";

    // then
    EXPECT_EQ(result, expected);
}
