#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source/extra/nlohmann_json.hpp>

TEST_CASE("nlohmann_json_properties") {
  {
    nlohmann::json json;
    auto properties = json.get<pqrs::osx::input_source::properties>();

    REQUIRE(properties.get_input_source_id() == std::nullopt);
    REQUIRE(properties.get_localized_name() == std::nullopt);
    REQUIRE(properties.get_languages().empty());
    REQUIRE(properties.get_first_language() == std::nullopt);
  }

  {
    pqrs::osx::input_source::properties properties;

    nlohmann::json json = properties;

    auto properties2 = json.get<pqrs::osx::input_source::properties>();
    REQUIRE(properties == properties2);
  }
  {
    pqrs::osx::input_source::properties properties;
    properties.set_input_source_id("com.apple.keylayout.US")
        .set_localized_name("U.S.")
        .set_languages(std::vector<std::string>{"en", "af", "asa", "bem"})
        .set_first_language("en");

    nlohmann::json json = properties;

    auto properties2 = json.get<pqrs::osx::input_source::properties>();
    REQUIRE(properties == properties2);
  }

  // Invalid json
  {
    nlohmann::json json;
    json["input_source_id"] = 123;
    json["localized_name"] = 123;
    json["languages"] = 123;
    json["first_language"] = 123;

    auto properties = json.get<pqrs::osx::input_source::properties>();

    REQUIRE(properties.get_input_source_id() == std::nullopt);
    REQUIRE(properties.get_localized_name() == std::nullopt);
    REQUIRE(properties.get_languages().empty());
    REQUIRE(properties.get_first_language() == std::nullopt);
  }

  // Invalid json (languages)
  {
    nlohmann::json json;
    json["input_source_id"] = 123;
    json["localized_name"] = 123;
    json["languages"] = nlohmann::json::array();
    json["languages"].push_back(123);
    json["first_language"] = 123;

    auto properties = json.get<pqrs::osx::input_source::properties>();

    REQUIRE(properties.get_input_source_id() == std::nullopt);
    REQUIRE(properties.get_localized_name() == std::nullopt);
    REQUIRE(properties.get_languages().empty());
    REQUIRE(properties.get_first_language() == std::nullopt);
  }
}
