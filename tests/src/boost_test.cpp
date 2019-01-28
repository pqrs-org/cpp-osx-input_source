#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source/extra/boost.hpp>

TEST_CASE("boost_properties") {
  pqrs::osx::input_source::properties p1;
  p1.set_input_source_id("com.apple.keylayout.US");

  pqrs::osx::input_source::properties p2;

  REQUIRE(boost::hash_value(p1) != boost::hash_value(p2));
}
