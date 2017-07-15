#pragma once

#include "util.hpp"

/**
 @brief Sentinel value appended to start/end of strings during typo check.

 @note Must not be \0 - std::string::length will report inaccurately.
 */
static const char sentinel = '\t';

/**
 @brief POD describing keyboard layout coordinates for a given character.

 @see find_char_in_table
 */
struct Coord {
  int row;
  int col;
};

/**
 @brief Hand used to press a given key.
 */
enum class Hand { Left = 0, Right = 1 };

/**
 @brief Finger used to press a given key - hand independent.
 */
enum class Finger { Pinky = 0, Ring = 1, Middle = 2, Pointer = 3 };

/**
 @brief Keyboard layout for coordinate finding.

 @see Coord
 @see find_char_in_table
 */
static const std::vector<std::vector<char>> key_table{
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
    {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';'},
    {'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.'}};

/**
 @brief Returns the coordinates for the given character c in the keyboard layout
 table.

 @see Coord
 */
auto find_char_in_table(const char c) -> Coord;

/**
 @brief Returns the hand used to strike a key at the given place.

 @see Hand
 @see find_char_in_table
 */
auto hand_for_char(const Coord place) -> Hand;

/**
 @brief Returns the finger used to strike a key at the given place, independent
 of hand.

 @see Finger
 @see find_char_in_table
 */
auto finger_for_char(const Coord place) -> Finger;

/**
 @brief Returns the distance between the lhs and rhs keys.

Formula is `dist = max(|row_1 - row_2|, |col_1 - col_2|)`.

 @see find_char_in_table
 */
auto distance(const Coord lhs, const Coord rhs) -> int;
