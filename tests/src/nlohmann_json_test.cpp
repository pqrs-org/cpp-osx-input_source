#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source/extra/nlohmann_json.hpp>

TEST_CASE("nlohmann_json_properties") {
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

  // from_json
  {
    auto json = nlohmann::json::object({
        {"input_source_id", "com.apple.keylayout.US"},
        {"localized_name", "U.S."},
        {"input_mode_id", "com.apple.inputmethod.Japanese"},
        {"languages", nlohmann::json::array({"en", "af", "asa", "bem"})},
        {"first_language", "en"},
    });
    auto properties = json.get<pqrs::osx::input_source::properties>();

    REQUIRE(properties.get_input_source_id() == "com.apple.keylayout.US");
    REQUIRE(properties.get_localized_name() == "U.S.");
    REQUIRE(properties.get_input_mode_id() == "com.apple.inputmethod.Japanese");
    REQUIRE(properties.get_languages() == std::vector<std::string>{"en", "af", "asa", "bem"});
    REQUIRE(properties.get_first_language() == "en");
  }

  // from_json (empty)
  {
    auto json = nlohmann::json::object();
    auto properties = json.get<pqrs::osx::input_source::properties>();

    REQUIRE(properties.get_input_source_id() == std::nullopt);
    REQUIRE(properties.get_localized_name() == std::nullopt);
    REQUIRE(properties.get_input_mode_id() == std::nullopt);
    REQUIRE(properties.get_languages().empty());
    REQUIRE(properties.get_first_language() == std::nullopt);
  }

  // type error

  {
    auto json = nlohmann::json();
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "json must be object, but is `null`");
  }

  // unknown key

  {
    auto json = nlohmann::json::object({
        {"input-source-id", "com.apple.keylayout.US"},
        {"localized_name", "U.S."},
        {"input_mode_id", "com.apple.inputmethod.Japanese"},
        {"languages", nlohmann::json::array({"en", "af", "asa", "bem"})},
        {"first_language", "en"},
    });
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "unknown key: `input-source-id`");
  }

  // type error (input_source_id)

  {
    auto json = nlohmann::json::object({
        {"input_source_id", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "`input_source_id` must be string, but is `null`");
  }

  // type error (localized_name)

  {
    auto json = nlohmann::json::object({
        {"localized_name", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "`localized_name` must be string, but is `null`");
  }

  // type_error (input_mode_id)

  {
    auto json = nlohmann::json::object({
        {"input_mode_id", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "`input_mode_id` must be string, but is `null`");
  }

  // type_error (languages)

  {
    auto json = nlohmann::json::object({
        {"languages", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "`languages` must be array, but is `null`");
  }

  // type_error (languages item)

  {
    auto json = nlohmann::json::object({
        {"languages", nlohmann::json::array({
                          "en",
                          "af",
                          nlohmann::json(),
                      })},
    });
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "`languages` must be array of strings, but is `[\"en\",\"af\",null]`");
  }

  // type_error (first_language)

  {
    auto json = nlohmann::json::object({
        {"first_language", nlohmann::json()},
    });
    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source::properties>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source::properties>(),
        "`first_language` must be string, but is `null`");
  }
}
