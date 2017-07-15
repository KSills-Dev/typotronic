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
  return max(row_diff, col_diff);
}

#ifdef TESTS_ENABLED
auto layout_test_find_char() -> bool {
  // Test each character
  if (find_char_in_table('1') != Coord{0, 0})
    return false;
  if (find_char_in_table('2') != Coord{0, 1})
    return false;
  if (find_char_in_table('3') != Coord{0, 2})
    return false;
  if (find_char_in_table('4') != Coord{0, 3})
    return false;
  if (find_char_in_table('5') != Coord{0, 4})
    return false;
  if (find_char_in_table('6') != Coord{0, 5})
    return false;
  if (find_char_in_table('7') != Coord{0, 6})
    return false;
  if (find_char_in_table('8') != Coord{0, 7})
    return false;
  if (find_char_in_table('9') != Coord{0, 8})
    return false;
  if (find_char_in_table('0') != Coord{0, 9})
    return false;
  if (find_char_in_table('q') != Coord{1, 0})
    return false;
  if (find_char_in_table('w') != Coord{1, 1})
    return false;
  if (find_char_in_table('e') != Coord{1, 2})
    return false;
  if (find_char_in_table('r') != Coord{1, 3})
    return false;
  if (find_char_in_table('t') != Coord{1, 4})
    return false;
  if (find_char_in_table('y') != Coord{1, 5})
    return false;
  if (find_char_in_table('u') != Coord{1, 6})
    return false;
  if (find_char_in_table('i') != Coord{1, 7})
    return false;
  if (find_char_in_table('o') != Coord{1, 8})
    return false;
  if (find_char_in_table('p') != Coord{1, 9})
    return false;
  if (find_char_in_table('a') != Coord{2, 0})
    return false;
  if (find_char_in_table('s') != Coord{2, 1})
    return false;
  if (find_char_in_table('d') != Coord{2, 2})
    return false;
  if (find_char_in_table('f') != Coord{2, 3})
    return false;
  if (find_char_in_table('g') != Coord{2, 4})
    return false;
  if (find_char_in_table('h') != Coord{2, 5})
    return false;
  if (find_char_in_table('j') != Coord{2, 6})
    return false;
  if (find_char_in_table('k') != Coord{2, 7})
    return false;
  if (find_char_in_table('l') != Coord{2, 8})
    return false;
  if (find_char_in_table(';') != Coord{2, 9})
    return false;
  if (find_char_in_table('z') != Coord{3, 0})
    return false;
  if (find_char_in_table('x') != Coord{3, 1})
    return false;
  if (find_char_in_table('c') != Coord{3, 2})
    return false;
  if (find_char_in_table('v') != Coord{3, 3})
    return false;
  if (find_char_in_table('b') != Coord{3, 4})
    return false;
  if (find_char_in_table('n') != Coord{3, 5})
    return false;
  if (find_char_in_table('m') != Coord{3, 6})
    return false;
  if (find_char_in_table(',') != Coord{3, 7})
    return false;
  if (find_char_in_table('.') != Coord{3, 8})
    return false;

  return true;
}

auto layout_test_find_hand() -> bool {
  // Test each col
  if (hand_for_char(Coord{0, 0}) != Hand::Left)
    return false;
  if (hand_for_char(Coord{0, 1}) != Hand::Left)
    return false;
  if (hand_for_char(Coord{0, 2}) != Hand::Left)
    return false;
  if (hand_for_char(Coord{0, 3}) != Hand::Left)
    return false;
  if (hand_for_char(Coord{0, 4}) != Hand::Left)
    return false;
  if (hand_for_char(Coord{0, 5}) != Hand::Right)
    return false;
  if (hand_for_char(Coord{0, 6}) != Hand::Right)
    return false;
  if (hand_for_char(Coord{0, 7}) != Hand::Right)
    return false;
  if (hand_for_char(Coord{0, 8}) != Hand::Right)
    return false;
  if (hand_for_char(Coord{0, 9}) != Hand::Right)
    return false;

  return true;
}

auto layout_test_find_finger() -> bool {
  // Test each col
  if (finger_for_char(Coord{0, 0}) != Finger::Pinky)
    return false;
  if (finger_for_char(Coord{0, 1}) != Finger::Ring)
    return false;
  if (finger_for_char(Coord{0, 2}) != Finger::Middle)
    return false;
  if (finger_for_char(Coord{0, 3}) != Finger::Index)
    return false;
  if (finger_for_char(Coord{0, 4}) != Finger::Index)
    return false;
  if (finger_for_char(Coord{0, 5}) != Finger::Index)
    return false;
  if (finger_for_char(Coord{0, 6}) != Finger::Index)
    return false;
  if (finger_for_char(Coord{0, 7}) != Finger::Middle)
    return false;
  if (finger_for_char(Coord{0, 8}) != Finger::Ring)
    return false;
  if (finger_for_char(Coord{0, 9}) != Finger::Pinky)
    return false;

  return true;
}

auto layout_test_distance() -> bool {
  // Test for all distances in each axis.
  if (distance(Coord{0, 0}, Coord{0, 1}) != 1)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 2}) != 2)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 3}) != 3)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 4}) != 4)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 5}) != 5)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 6}) != 6)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 7}) != 7)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 8}) != 8)
    return false;
  if (distance(Coord{0, 0}, Coord{0, 9}) != 9)
    return false;
  if (distance(Coord{0, 0}, Coord{1, 0}) != 1)
    return false;
  if (distance(Coord{0, 0}, Coord{2, 0}) != 2)
    return false;
  if (distance(Coord{0, 0}, Coord{3, 0}) != 3)
    return false;
  if (distance(Coord{0, 0}, Coord{4, 0}) != 4)
    return false;
  if (distance(Coord{0, 0}, Coord{5, 0}) != 5)
    return false;
  if (distance(Coord{0, 0}, Coord{6, 0}) != 6)
    return false;
  if (distance(Coord{0, 0}, Coord{7, 0}) != 7)
    return false;
  if (distance(Coord{0, 0}, Coord{8, 0}) != 8)
    return false;
  if (distance(Coord{0, 0}, Coord{9, 0}) != 9)
    return false;

  // Test max distance is selected
  if (distance(Coord{0, 1}, Coord{8, 8}) != 8)
    return false;

  return true;
}
#endif
