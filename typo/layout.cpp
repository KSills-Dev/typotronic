#include "layout.hpp"
#include <cstddef>

/**
 @brief
 */
auto find_char_in_table(const char c) -> Coord {
  for (size_t i = 0; i < key_table.size(); i++) {
    for (size_t j = 0; j < key_table[i].size(); j++) {
      if (key_table[i][j] == c)
        return Coord{static_cast<int>(i), static_cast<int>(j)};
    }
  }
  return Coord();
}

/**
 @brief
 */
auto hand_for_char(const Coord place) -> Hand {
  return (place.col / 5 == 1) ? Hand::Left : Hand::Right;
}

/**
 @brief
 */
auto finger_for_char(const Coord place) -> Finger {
  auto col = place.col;
  if (col / 5 == 1) {
    col = col * -1 + 9;
  }
  col = (col == 4) ? 3 : col;
  return static_cast<Finger>(col);
}

auto distance(const Coord lhs, const Coord rhs) -> int {
  auto row_diff = (lhs.row > rhs.row) ? lhs.row - rhs.row : rhs.row - lhs.row;
  auto col_diff = (lhs.col > rhs.col) ? lhs.col - rhs.col : rhs.col - lhs.col;
  return max({row_diff, col_diff});
}
