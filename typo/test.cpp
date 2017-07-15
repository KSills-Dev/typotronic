#include <iostream>

#include "layout.hpp"

auto print_result(const std::string &name, const bool result) -> bool {
  std::cout << "\t" << name << " "
            << ((result) ? "\e[32mPassed" : "\e[31mFailed") << "\e[0m\n";
  return result;
}

auto main() -> int {
  std::cout << "Layout\n";
  print_result("find_char_in_table", layout_test_find_char());
  print_result("hand_for_char", layout_test_find_hand());
  print_result("finger_for_char", layout_test_find_finger());
  print_result("distance", layout_test_distance());
}
