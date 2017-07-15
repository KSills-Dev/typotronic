#include "typo.hpp"

#include <iostream>

auto main(const int argc, const char **argv) -> int {
  std::cout << "I'm not a stub anymore!\n\n";

  const std::string correct = "the rain in spain stays mainly on the plain";
  const std::string actual = "teh driafna i pasin staya ksjnmly in th eplani";

  const auto result = find_typos(correct, actual);

  std::cout << "Final cost: " << result.first;
  std::cout << "\n---\n";
  for (const auto &entry : result.second) {
    std::cout << entry << std::endl;
  }
}
