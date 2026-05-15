#include <string>

#include "jsonschemabuildertest.hpp"

#include "jsonservice/jsonschemabuilder.hpp"

using namespace JsonService;
using namespace nlohmann;

TEST_F(JsonSchemaBuilderTest, ElementBuilder_setProperty_InOrder)
{
    // setup
    auto builder = JsonSchemaElementBuilder();

    builder.setProperty("key", "value");
    builder.setProperty("number", 42);
    builder.setProperty("complex", json::parse("{}"));

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
    auto builder = JsonSchemaBuilder("ignored");

    builder.setRequired({"foo"});
    builder.setAdditionalProperties(json::object());

    builder.addProperty("property");
    builder.addProperty("typedProperty", IJsonServiceTypes::JsonType::BOOLEAN);
    builder.addReference("ref", "ref-def", IJsonServiceTypes::JsonType::OBJECT, false);

    // when
    std::string result = builder.build(false).dump(2);
    std::string expected = R"({
  "properties": {
    "property": {},
    "typedProperty": {
      "type": "boolean"
    },
    "ref": {
      "$ref": "#/$defs/ref-def",
      "type": "object"
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
    auto builder = JsonSchemaBuilder("target");

    builder.addProperty("empty");
    builder.addProperty("defaulted").setDefault("value");
    builder.addReference("recursive", builder);

    // when
    std::string result = builder.build(false).dump(2);
    std::string expected = R"({
  "properties": {
    "empty": {},
    "defaulted": {
      "default": "value"
    },
    "recursive": {
      "$ref": "#/$defs/target",
      "type": "object",
      "default": {
        "defaulted": "value"
      }
    }
  },
  "$defs": {
    "target": {
      "properties": {
        "empty": {},
        "defaulted": {
          "default": "value"
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
    auto subSchema = JsonSchemaBuilder("subSchema");
    subSchema.addProperty("prop").setDefault("default");

    auto builder = JsonSchemaBuilder();
    builder.addReference("property", subSchema);

    // when
    std::string result = builder.build().dump(2);
    std::string expected = R"({
  "$schema": "http://json-schema.org/draft-07/schema#",
  "properties": {
    "property": {
      "$ref": "#/$defs/subSchema",
      "type": "object",
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
