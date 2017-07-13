#include "util.hpp"
#include <cstddef>

auto min(std::vector<int> values) -> int {
  auto min = values[0];
  for (size_t i = 1; i < values.size(); i++) {
    if (values[i] < min) {
      min = values[i];
    }
  }
  return min;
}

auto max(std::vector<int> values) -> int {
  auto max = values[0];
  for (size_t i = 1; i < values.size(); i++) {
    if (values[i] > max) {
      max = values[i];
    }
  }
  return max;
}
