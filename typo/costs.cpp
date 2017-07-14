#include "costs.hpp"

#include "layout.hpp"

auto compute_insert_cost(const char left, const char curr, const char right)
    -> int {
  if (curr == left) {
    return cost::insert_repeat;
  }

  int minv = cost::max_cost;
  const auto place_left = find_char_in_table(left);
  const auto place_curr = find_char_in_table(curr);
  const auto place_right = find_char_in_table(right);

  if (curr == ' ') {
    if (place_left.row == 3) {
      return cost::insert_space_ab;
    }
  }

  if (left != ' ' && left != sentinel &&
      hand_for_char(place_left) == hand_for_char(place_curr)) {
    minv = min({minv, distance(place_left, place_curr)});
  } else {
    minv = min({minv, cost::insert_char_oh});
  }

  if (right != ' ' && right != sentinel &&
      hand_for_char(place_right) == hand_for_char(place_curr)) {
    minv = min({minv, distance(place_right, place_curr)});
  } else {
    minv = min({minv, cost::insert_char_oh});
  }

  return minv;
}

auto compute_delete_cost(const char left, const char curr) -> int {
  if (left == curr) {
    return cost::delete_repeat;
  }

  if (curr == ' ') {
    return cost::delete_space;
  }
  if (left == sentinel || left == ' ') {
    return cost::delete_char_fc;
  }

  const auto place_left = find_char_in_table(left);
  const auto place_curr = find_char_in_table(curr);
  if (hand_for_char(place_left) == hand_for_char(place_curr)) {
    return cost::delete_char_sh;
  } else {
    return cost::delete_char_oh;
  }
}

auto compute_substitute_cost(const char correct, const char actual) -> int {
  if (correct == ' ' || actual == ' ') {
    return cost::sub_space_char;
  }

  const auto place_correct = find_char_in_table(correct);
  const auto place_actual = find_char_in_table(actual);
  if (hand_for_char(place_correct) != hand_for_char(place_actual)) {
    if (finger_for_char(place_correct) == finger_for_char(place_actual)) {
      return cost::sub_char_sf;
    } else {
      return cost::sub_char_oh;
    }
  } else {
    return distance(place_correct, place_actual);
  }
}

auto compute_transpose_cost(const char left, const char curr) -> int {
  if (left == ' ' || curr == ' ') {
    return cost::trans_space;
  }

  if (hand_for_char(find_char_in_table(left)) ==
      hand_for_char(find_char_in_table(curr))) {
    return cost::trans_char_sh;
  } else {
    return cost::trans_char_oh;
  }
}
