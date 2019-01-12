#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/osx/input_source.hpp>

TEST_CASE("input_source") {
  REQUIRE(pqrs::osx::input_source::make_input_source_id(nullptr) == std::nullopt);
  REQUIRE(pqrs::osx::input_source::make_input_mode_id(nullptr) == std::nullopt);
  REQUIRE(pqrs::osx::input_source::make_languages(nullptr).empty());
}

TEST_CASE("properties") {
  {
    pqrs::osx::input_source::properties properties;
    REQUIRE(properties.get_input_source_id() == std::nullopt);
    REQUIRE(properties.get_localized_name() == std::nullopt);
    REQUIRE(properties.get_input_mode_id() == std::nullopt);
    REQUIRE(properties.get_languages().empty());
    REQUIRE(properties.get_first_language() == std::nullopt);
  }

  {
    pqrs::osx::input_source::properties properties;
    properties.set_input_source_id("com.apple.keylayout.US")
        .set_localized_name("U.S.")
        .set_languages(std::vector<std::string>{"en", "af", "asa", "bem"})
        .set_first_language("en");

    REQUIRE(properties.get_input_source_id() == "com.apple.keylayout.US");
    REQUIRE(properties.get_localized_name() == "U.S.");
    REQUIRE(properties.get_input_mode_id() == std::nullopt);
    REQUIRE(properties.get_languages().size() == 4);
    REQUIRE(properties.get_languages()[0] == "en");
    REQUIRE(properties.get_languages()[1] == "af");
    REQUIRE(properties.get_languages()[2] == "asa");
    REQUIRE(properties.get_languages()[3] == "bem");
    REQUIRE(properties.get_first_language() == "en");
  }

  {
    pqrs::osx::input_source::properties properties;
    properties.set_input_source_id("com.apple.inputmethod.SCIM.ITABC")
        .set_localized_name("Pinyin - Simplified")
        .set_input_mode_id("com.apple.inputmethod.SCIM.ITABC")
        .set_languages(std::vector<std::string>{"zh-Hans"})
        .set_first_language("zh-Hans");

    REQUIRE(properties.get_input_source_id() == "com.apple.inputmethod.SCIM.ITABC");
    REQUIRE(properties.get_localized_name() == "Pinyin - Simplified");
    REQUIRE(properties.get_input_mode_id() == "com.apple.inputmethod.SCIM.ITABC");
    REQUIRE(properties.get_languages().size() == 1);
    REQUIRE(properties.get_languages()[0] == "zh-Hans");
    REQUIRE(properties.get_first_language() == "zh-Hans");
  }
}
