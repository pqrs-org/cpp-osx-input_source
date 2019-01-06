#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/osx/input_source.hpp>

TEST_CASE("input_source") {
  REQUIRE(pqrs::osx::input_source::make_input_source_id(nullptr) == std::nullopt);
  REQUIRE(pqrs::osx::input_source::make_input_mode_id(nullptr) == std::nullopt);
  REQUIRE(pqrs::osx::input_source::make_languages(nullptr).empty());
}
