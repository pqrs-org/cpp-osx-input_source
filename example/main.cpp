#include <iostream>
#include <pqrs/osx/input_source.hpp>

namespace {
void output_input_source(TISInputSourceRef input_source) {
  if (input_source) {
    pqrs::osx::input_source::properties properties(input_source);

    if (auto& input_source_id = properties.get_input_source_id()) {
      std::cout << "  input_source_id: " << *input_source_id << std::endl;
    }

    if (auto& localized_name = properties.get_localized_name()) {
      std::cout << "  localized_name: " << *localized_name << std::endl;
    }

    if (auto& input_mode_id = properties.get_input_mode_id()) {
      std::cout << "  input_mode_id: " << *input_mode_id << std::endl;
    }

    auto& languages = properties.get_languages();
    if (!languages.empty()) {
      std::cout << "  language:";
      for (const auto& l : languages) {
        std::cout << " " << l;
      }
      std::cout << std::endl;
    }

    if (auto& first_language = properties.get_first_language()) {
      std::cout << "  first_language: " << *first_language << std::endl;
    }
  }
}
} // namespace

int main(void) {
  if (auto input_source = pqrs::osx::input_source::make_current_keyboard_input_source()) {
    std::cout << "current_keyboard_input_source" << std::endl;
    output_input_source(*input_source);
    std::cout << std::endl;
  }

  for (const auto& input_source : pqrs::osx::input_source::make_selectable_keyboard_input_sources()) {
    std::cout << "selectable_keyboard_input_source" << std::endl;
    output_input_source(*input_source);
    std::cout << std::endl;
  }

  return 0;
}
