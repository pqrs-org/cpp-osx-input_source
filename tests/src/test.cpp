#include "boost_test.hpp"
#include "nlohmann_json_test.hpp"
#include <boost/ut.hpp>
#include <pqrs/osx/input_source.hpp>
#include <unordered_set>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "input_source"_test = [] {
    expect(pqrs::osx::input_source::make_input_source_id(nullptr) == std::nullopt);
    expect(pqrs::osx::input_source::make_input_mode_id(nullptr) == std::nullopt);
    expect(pqrs::osx::input_source::make_languages(nullptr).empty());
  };

  "properties"_test = [] {
    {
      pqrs::osx::input_source::properties properties;
      expect(properties.get_input_source_id() == std::nullopt);
      expect(properties.get_localized_name() == std::nullopt);
      expect(properties.get_input_mode_id() == std::nullopt);
      expect(properties.get_languages().empty());
      expect(properties.get_first_language() == std::nullopt);
    }

    {
      pqrs::osx::input_source::properties properties;
      properties.set_input_source_id("com.apple.keylayout.US")
          .set_localized_name("U.S.")
          .set_languages(std::vector<std::string>{"en", "af", "asa", "bem"})
          .set_first_language("en");

      expect(properties.get_input_source_id() == "com.apple.keylayout.US");
      expect(properties.get_localized_name() == "U.S.");
      expect(properties.get_input_mode_id() == std::nullopt);
      expect(properties.get_languages().size() == 4);
      expect(properties.get_languages()[0] == "en");
      expect(properties.get_languages()[1] == "af");
      expect(properties.get_languages()[2] == "asa");
      expect(properties.get_languages()[3] == "bem");
      expect(properties.get_first_language() == "en");
    }

    {
      pqrs::osx::input_source::properties properties;
      properties.set_input_source_id("com.apple.inputmethod.SCIM.ITABC")
          .set_localized_name("Pinyin - Simplified")
          .set_input_mode_id("com.apple.inputmethod.SCIM.ITABC")
          .set_languages(std::vector<std::string>{"zh-Hans"})
          .set_first_language("zh-Hans");

      expect(properties.get_input_source_id() == "com.apple.inputmethod.SCIM.ITABC");
      expect(properties.get_localized_name() == "Pinyin - Simplified");
      expect(properties.get_input_mode_id() == "com.apple.inputmethod.SCIM.ITABC");
      expect(properties.get_languages().size() == 1);
      expect(properties.get_languages()[0] == "zh-Hans");
      expect(properties.get_first_language() == "zh-Hans");
    }
  };

  "properties operator=="_test = [] {
    {
      pqrs::osx::input_source::properties properties1;
      pqrs::osx::input_source::properties properties2;
      expect(properties1 == properties2);

      properties1.set_input_source_id("com.apple.keylayout.US");
      expect(properties1 != properties2);

      properties2.set_input_source_id("com.apple.keylayout.US");
      expect(properties1 == properties2);

      properties1.set_languages(std::vector<std::string>{"en", "af", "asa", "bem"});
      expect(properties1 != properties2);

      properties2.set_languages(std::vector<std::string>{"en", "af", "asa"});
      expect(properties1 != properties2);

      properties2.set_languages(std::vector<std::string>{"en", "af", "asa", "bem"});
      expect(properties1 == properties2);
    }
  };

  "properties hash"_test = [] {
    std::unordered_set<pqrs::osx::input_source::properties> set;

    {
      pqrs::osx::input_source::properties properties;
      properties.set_input_source_id("com.apple.keylayout.US");
      set.insert(properties);
    }

    {
      pqrs::osx::input_source::properties p1;
      p1.set_input_source_id("com.apple.keylayout.US");

      pqrs::osx::input_source::properties p2;

      expect(std::hash<pqrs::osx::input_source::properties>{}(p1) !=
             std::hash<pqrs::osx::input_source::properties>{}(p2));
    }
  };

  run_boost_test();
  run_nlohmann_json_test();

  return 0;
}
