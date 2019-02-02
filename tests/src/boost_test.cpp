#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source/extra/boost.hpp>

TEST_CASE("boost_properties") {
  {
    pqrs::osx::input_source::properties p;
    p.set_input_source_id("com.apple.keylayout.US");

    REQUIRE(std::hash<pqrs::osx::input_source::properties>{}(p) ==
            pqrs::osx::input_source::hash_value(p));
  }
}
