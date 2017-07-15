#pragma once

#include <cstddef>
#include <vector>

/**
 @brief Returns the minimum value from a pair of elements.
 */
template <typename T> auto min(const T &lhs, const T &rhs) -> T {
  return (lhs < rhs) ? lhs : rhs;
}

/**
 @brief Returns the maximum value from a pair of elements.
 */
template <typename T> auto max(const T &lhs, const T &rhs) -> T {
  return (lhs > rhs) ? lhs : rhs;
}

/**
 @brief Returns the minimum value from a vector of elements.
 */
template <typename T> auto min(std::vector<T> values) -> T {
  auto min = values[0];
  for (size_t i = 1; i < values.size(); i++) {
    if (values[i] < min) {
      min = values[i];
    }
  }
  return min;
}

/**
 @brief Returns the maximum value from a vector of elements.
 */
template <typename T> auto max(std::vector<T> values) -> T {
  auto max = values[0];
  for (size_t i = 1; i < values.size(); i++) {
    if (values[i] > max) {
      max = values[i];
    }
  }
  return max;
}
