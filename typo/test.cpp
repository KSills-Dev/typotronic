#include <iostream>

auto main() -> int {
  std::cout << "Empty test build!\n";

#ifdef TESTS_ENABLED
  std::cout << "But tests ARE enabled!\n";
#endif
}
