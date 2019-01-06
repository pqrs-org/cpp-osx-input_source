#include <iostream>
#include <pqrs/osx/input_source.hpp>

namespace {
void output_input_source(TISInputSourceRef input_source) {
  if (input_source) {
    if (auto input_source_id = pqrs::osx::input_source::make_input_source_id(input_source)) {
      std::cout << "  input_source_id: " << *input_source_id << std::endl;
    }

    if (auto localized_name = pqrs::osx::input_source::make_localized_name(input_source)) {
      std::cout << "  localized_name: " << *localized_name << std::endl;
    }

    if (auto input_mode_id = pqrs::osx::input_source::make_input_mode_id(input_source)) {
      std::cout << "  input_mode_id: " << *input_mode_id << std::endl;
    }

    auto languages = pqrs::osx::input_source::make_languages(input_source);
    if (!languages.empty()) {
      std::cout << "  language:";
      for (const auto& l : languages) {
        std::cout << " " << l;
      }
      std::cout << std::endl;
    }

    if (auto first_language = pqrs::osx::input_source::make_first_language(input_source)) {
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
