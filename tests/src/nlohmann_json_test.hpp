#include <boost/ut.hpp>
#include <iostream>
#include <pqrs/osx/input_source/extra/nlohmann_json.hpp>

void run_nlohmann_json_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "nlohmann_json_properties"_test = [] {
    {
      pqrs::osx::input_source::properties properties;

      nlohmann::json json = properties;

      auto properties2 = json.get<pqrs::osx::input_source::properties>();
      expect(properties == properties2);
    }
    {
      pqrs::osx::input_source::properties properties;
      properties.set_input_source_id("com.apple.keylayout.US")
          .set_localized_name("U.S.")
          .set_languages(std::vector<std::string>{"en", "af", "asa", "bem"})
          .set_first_language("en");

      nlohmann::json json = properties;

      auto properties2 = json.get<pqrs::osx::input_source::properties>();
      expect(properties == properties2);
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

      expect(properties.get_input_source_id() == "com.apple.keylayout.US");
      expect(properties.get_localized_name() == "U.S.");
      expect(properties.get_input_mode_id() == "com.apple.inputmethod.Japanese");
      expect(properties.get_languages() == std::vector<std::string>{"en", "af", "asa", "bem"});
      expect(properties.get_first_language() == "en");
    }

    // from_json (empty)
    {
      auto json = nlohmann::json::object();
      auto properties = json.get<pqrs::osx::input_source::properties>();

      expect(properties.get_input_source_id() == std::nullopt);
      expect(properties.get_localized_name() == std::nullopt);
      expect(properties.get_input_mode_id() == std::nullopt);
      expect(properties.get_languages().empty());
      expect(properties.get_first_language() == std::nullopt);
    }

    // type error

    try {
      auto json = nlohmann::json();
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("json must be object, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // unknown key

    try {
      auto json = nlohmann::json::object({
          {"input-source-id", "com.apple.keylayout.US"},
          {"localized_name", "U.S."},
          {"input_mode_id", "com.apple.inputmethod.Japanese"},
          {"languages", nlohmann::json::array({"en", "af", "asa", "bem"})},
          {"first_language", "en"},
      });
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("unknown key: `input-source-id`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type error (input_source_id)

    try {
      auto json = nlohmann::json::object({
          {"input_source_id", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`input_source_id` must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type error (localized_name)

    try {
      auto json = nlohmann::json::object({
          {"localized_name", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`localized_name` must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type_error (input_mode_id)

    try {
      auto json = nlohmann::json::object({
          {"input_mode_id", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`input_mode_id` must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type_error (languages)

    try {
      auto json = nlohmann::json::object({
          {"languages", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`languages` must be array, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type_error (languages item)

    try {
      auto json = nlohmann::json::object({
          {"languages", nlohmann::json::array({
                            "en",
                            "af",
                            nlohmann::json(),
                        })},
      });
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`languages` entry must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type_error (first_language)

    try {
      auto json = nlohmann::json::object({
          {"first_language", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source::properties>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`first_language` must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }
  };
}
