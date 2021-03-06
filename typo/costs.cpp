#include "costs.hpp"

#include "layout.hpp"

#include <algorithm>

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
    } else {
      return cost::insert_space_ae;
    }
  }

  if (left != ' ' && left != sentinel) {
    if (hand_for_char(place_left) == hand_for_char(place_curr)) {
      minv = std::min(minv, distance(place_left, place_curr));
    } else {
      minv = std::min(minv, cost::insert_char_oh);
    }
  }

  if (right != ' ' && right != sentinel) {
    if (hand_for_char(place_right) == hand_for_char(place_curr)) {
      minv = std::min(minv, distance(place_right, place_curr));
    } else {
      minv = std::min(minv, cost::insert_char_oh);
    }
  }

  return minv;
}

auto compute_delete_cost(const char left, const char corr) -> int {
  if (left == corr) {
    return cost::delete_repeat;
  }

  if (corr == ' ') {
    return cost::delete_space;
  }
  if (left == sentinel || left == ' ') {
    return cost::delete_char_fc;
  }

  const auto place_left = find_char_in_table(left);
  const auto place_corr = find_char_in_table(corr);
  if (hand_for_char(place_left) == hand_for_char(place_corr)) {
    return cost::delete_char_sh;
  } else {
    return cost::delete_char_oh;
  }
}

auto compute_substitute_cost(const char correct, const char actual) -> int {
  if (correct == ' ' || actual == ' ') {
    return cost::sub_space;
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

#ifdef TESTS_ENABLED

auto cost_test_compute_insert() -> bool {
  // Repeat
  if (compute_insert_cost('a', 'a', 'a') != cost::insert_repeat)
    return false;
  // Space After Bottom Row
  if (compute_insert_cost('v', ' ', 'v') != cost::insert_space_ab)
    return false;
  // Space After Else
  if (compute_insert_cost('a', ' ', 'a') != cost::insert_space_ae)
    return false;
  // Character Before Space
  if (compute_insert_cost(' ', 'a', ' ') != cost::insert_char_bs)
    return false;
  // Before/After Same Hand
  if (compute_insert_cost('a', 's', 'd') != 1)
    return false;
  // Before/After Opposite Hand
  if (compute_insert_cost('j', 's', 'l') != cost::insert_char_oh)
    return false;

  return true;
}

auto cost_test_compute_delete() -> bool {
  // Repeat
  if (compute_delete_cost('a', 'a') != cost::delete_repeat)
    return false;
  // Space
  if (compute_delete_cost('a', ' ') != cost::delete_space)
    return false;
  // After Same Hand
  if (compute_delete_cost('a', 's') != cost::delete_char_sh)
    return false;
  // After Fifferent Hand
  if (compute_delete_cost('a', 'l') != cost::delete_char_oh)
    return false;
  // First in String
  if (compute_delete_cost(sentinel, 'a') != cost::delete_char_fc)
    return false;

  return true;
}

auto cost_test_compute_substitute() -> bool {
  // Space
  if (compute_substitute_cost(' ', 's') != cost::sub_space)
    return false;
  // Same Hand
  if (compute_substitute_cost('a', 's') != 1)
    return false;
  // Other Hand, Same Finger
  if (compute_substitute_cost('a', ';') != cost::sub_char_sf)
    return false;
  // Other Hand, Different Finger
  if (compute_substitute_cost('a', 'k') != cost::sub_char_oh)
    return false;

  return true;
}

auto cost_test_compute_transpose() -> bool {
  // Space
  if (compute_transpose_cost('a', ' ') != cost::trans_space)
    return false;
  // Same Hand
  if (compute_transpose_cost('s', 'a') != cost::trans_char_sh)
    return false;
  // Different Hand
  if (compute_transpose_cost('a', 'l') != cost::trans_char_oh)
    return false;

  return true;
}

#endif
