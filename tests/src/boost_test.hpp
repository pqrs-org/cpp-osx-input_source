#include <boost/ut.hpp>
#include <iostream>
#include <pqrs/osx/input_source/extra/boost.hpp>

void run_boost_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "boost_properties"_test = [] {
    {
      pqrs::osx::input_source::properties p;
      p.set_input_source_id("com.apple.keylayout.US");

      expect(std::hash<pqrs::osx::input_source::properties>{}(p) ==
             pqrs::osx::input_source::hash_value(p));
    }
  };
}
