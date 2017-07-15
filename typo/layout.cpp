#include "layout.hpp"
#include <cstddef>

auto find_char_in_table(const char c) -> Coord {
  for (size_t i = 0; i < key_table.size(); i++) {
    for (size_t j = 0; j < key_table[i].size(); j++) {
      if (key_table[i][j] == c)
        // Key found, return coordinate.
        return Coord{static_cast<int>(i), static_cast<int>(j)};
    }
  }
  return Coord();
}

auto hand_for_char(const Coord place) -> Hand {
  // Left hand col < 5, right hand col >= 5.
  return static_cast<Hand>(place.col / 5);
}

auto finger_for_char(const Coord place) -> Finger {
  auto col = place.col;

  if (col / 5 == 1) {
    // Invert order and reduce value for right hand.
    col = col * -1 + 9;
  }

  // Index finger used for last 2 columns each hand.
  col = (col == 4) ? 3 : col;
  return static_cast<Finger>(col);
}

auto distance(const Coord lhs, const Coord rhs) -> int {
  auto row_diff = (lhs.row > rhs.row) ? lhs.row - rhs.row : rhs.row - lhs.row;
  auto col_diff = (lhs.col > rhs.col) ? lhs.col - rhs.col : rhs.col - lhs.col;
  return max({row_diff, col_diff});
}
