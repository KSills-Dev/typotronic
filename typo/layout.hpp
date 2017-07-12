#pragma once

#include "util.hpp"

/**
 @brief
 */
struct Coord {
  int row;
  int col;
};

/**
 @brief
 */
enum class Hand { Left, Right };

/**
 @brief
 */
enum class Finger { Pinky = 0, Ring = 1, Middle = 2, Pointer = 3 };

/**
 @brief
 */
static const std::vector<std::vector<char>> key_table{
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
    {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';'},
    {'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.'}};

/**
 @brief
 */
auto find_char_in_table(const char c) -> Coord;

/**
 @brief
 */
auto hand_for_char(const Coord place) -> Hand;

/**
 @brief
 */
auto finger_for_char(const Coord place) -> Finger;

auto distance(const Coord lhs, const Coord rhs) -> int;
}