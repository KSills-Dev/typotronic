#include "typo.hpp"
#include "costs.hpp"
#include "layout.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

auto operator<<(std::ostream &stream, const TypoKind kind) -> std::ostream & {
  switch (kind) {
  case TypoKind::None: {
    break;
  }
  case TypoKind::Substitute: {
    stream << "Substitute";
  }
  case TypoKind::Insert: {
    stream << "Insert";
    break;
  }
  case TypoKind::Delete: {
    stream << "Delete";
    break;
  }
  case TypoKind::Transpose: {
    stream << "Transpose";
    break;
  }
  default: {
    stream << "POORLY-FORMED-TYPO\n";
    break;
  }
  }

  return stream;
}

auto Typo::to_string() const -> std::string {
  switch (kind) {
  case TypoKind::None: {
    return "";
    break;
  }
  case TypoKind::Substitute: {
    return std::string("Substitute ") + c + " at " + std::to_string(idx);
  }
  case TypoKind::Insert: {
    return std::string("Insert ") + c + " before " + std::to_string(idx);
    break;
  }
  case TypoKind::Delete: {
    return std::string("Delete ") + std::to_string(idx);
    break;
  }
  case TypoKind::Transpose: {
    return std::string("Transpose ") + std::to_string(idx) + "-" +
           std::to_string(idx + 1);
    break;
  }
  default: {
    return "POORLY-FORMED-TYPO\n";
    break;
  }
  }
}

auto operator<<(std::ostream &stream, const Typo typo) -> std::ostream & {
  stream << typo.to_string();
  return stream;
}

auto find_tranpose(TransposeList &data, const std::string &correct,
                   const std::string &actual) -> void {
  for (auto i = correct.size() - 1; i > 1; --i) {
    for (auto j = actual.size() - 1; j > 1; --j) {
      const auto corr = correct[i];
      const auto curr = actual[j];
      const auto left = actual[j - 1];

      if (left == corr && curr != corr) {
        if (data.count(i * actual.size() + j) > 0) {
          continue;
        }

        std::array<int, max_tranpose_distance> working{};
        working.fill(-1);
        auto found = false;
        auto running_cost = compute_transpose_cost(left, curr);
        for (auto n = 1; n < max_tranpose_distance && ((i-n)>1) && ((j-1-n)>1); n++) {
          const auto corr = correct[i - n];
          const auto left = actual[j - 1 - n];

          if (curr == corr) {
            working[n - 1] = running_cost;
            found = true;
          } else {
            working[n - 1] = -1;
          }
          if (corr != left) {
            break;
          }
          running_cost += compute_transpose_cost(left, curr);
        }
        if (found) {
          data[i * actual.size() + j] = working;
        }
      }
    }
  }
}

auto find_typos(const TypoTable &table, const int place) -> TypoStack {
  if (place == 0) {
    return TypoStack{};
  }

  const auto entry = table[place];
  const auto typo = entry.typo;

  auto result = find_typos(table, entry.parent);

  if (typo.kind == TypoKind::Transpose) {
    // Transposition Expansion
    for (auto i = 0; i < typo.n; i++) {
      result.push_back(Typo{typo.kind, typo.idx + i, typo.n});
    }
  } else if (typo.kind != TypoKind::None) {
    result.push_back(typo);
  }

  return result;
}

auto fill_table(TypoTable &table, const TransposeList &transposes,
                const std::string &correct, const std::string &actual, int i,
                int j) -> int {
  if (i == 0 && j == 0) {
    // Both strings consumed
    return 0;
  }

  const auto col = (actual.size() - 1);
  const auto row = 1;
  const auto place = i * col + j * row;

  if (table[place].parent != -1) {
    // Entry already made
    return table[place].cost;
  }

  if (i == 0) {
    // Correct string consumed
    table[place].typo = Typo(TypoKind::Insert, j - 1, actual[j]);
    table[place].parent = place - row;
    table[place].cost =
        fill_table(table, transposes, correct, actual, i, j - 1);
    table[place].cost +=
        compute_insert_cost(actual[j - 1], actual[j], actual[j + 1]);
    return table[place].cost;
  }
  if (j == 0) {
    // Actual string consumed
    table[place].typo = Typo(TypoKind::Delete, j, correct[i]);
    table[place].parent = place - col;
    table[place].cost =
        fill_table(table, transposes, correct, actual, i - 1, j);
    table[place].cost += compute_delete_cost(sentinel, correct[i]);
    return table[place].cost;
  }

  // Fetch table at possible locations
  const auto cost_after_insert =
      fill_table(table, transposes, correct, actual, i, j - 1);
  const auto cost_after_delete =
      fill_table(table, transposes, correct, actual, i - 1, j);
  const auto cost_after_sub_skip =
      fill_table(table, transposes, correct, actual, i - 1, j - 1);

  // Other possibilities
  std::vector<TypoCell> options{
      TypoCell(Typo(TypoKind::Insert, j - 1, actual[j]),
               compute_insert_cost(actual[j - 1], actual[j], actual[j + 1]) +
                   cost_after_insert,
               place - row),
      TypoCell(Typo(TypoKind::Delete, j, correct[i]),
               compute_delete_cost(actual[j], correct[i]) + cost_after_delete,
               place - col)};

  // Matching characters
  if (correct[i] == actual[j]) {
    options.emplace_back(Typo(), cost_after_sub_skip, place - col - row);
  } else {
    options.emplace_back(Typo(TypoKind::Substitute, j - 1, actual[j]),
                         compute_substitute_cost(correct[i], actual[j]) +
                             cost_after_sub_skip,
                         place - col - row);
  }

  // Check possible tranposes
  if (transposes.count(place)) {
    const auto transpose_array = transposes.at(place);
    for (size_t n = 0; n < max_tranpose_distance; n++) {
      const auto tcost = transpose_array[n];
      if (tcost != -1) {
        options.emplace_back(Typo(TypoKind::Transpose, j - 2 - n, n + 1),
                             tcost + fill_table(table, transposes, correct,
                                                actual, i - (n + 2),
                                                j - (n + 2)),
                             place - (col * (n + 2)) - row * (n + 2));
      }
    }
  }

  table[place] = *std::min_element(options.begin(), options.end());
  return table[place].cost;
}

auto find_typos(const std::string &correct, const std::string &actual)
    -> std::pair<int, TypoStack> {
  const auto new_correct = sentinel + correct;
  const auto new_actual = sentinel + actual + sentinel;

  TransposeList transposes{};
  find_tranpose(transposes, sentinel + correct, sentinel + actual);

  TypoTable data{new_correct.size() * (new_actual.size() - 1)};
  fill_table(data, transposes, new_correct, new_actual, new_correct.size() - 1,
             new_actual.size() - 2);

  const auto final_cost =
      data[new_correct.size() * (new_actual.size() - 1) - 1].cost;

  const auto typos =
      find_typos(data, new_correct.size() * (new_actual.size() - 1) - 1);

  return std::make_pair(final_cost, typos);
}
