#include "typo.hpp"
#include "costs.hpp"
#include "layout.hpp"

#include <iomanip>
#include <iostream>

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
        auto running_cost = 0;
        for (auto n = 1; n < max_tranpose_distance; n++) {
          const auto corr = correct[i - n];
          const auto left = actual[j - 1 - n];

          running_cost += compute_transpose_cost(left, curr);
          if (curr == corr) {
            working[n - 1] = running_cost;
            found = true;
          } else {
            working[n - 1] = -1;
          }
          if (corr != left) {
            break;
          }
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
  } else {
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
  const auto cost_insert =
      fill_table(table, transposes, correct, actual, i, j - 1);
  const auto cost_delete =
      fill_table(table, transposes, correct, actual, i - 1, j);
  const auto cost_sub_skip =
      fill_table(table, transposes, correct, actual, i - 1, j - 1);

  // Other possibilities
  std::vector<TypoCell> options{
      TypoCell(Typo(TypoKind::Insert, j - 1, actual[j]),
               compute_insert_cost(actual[j - 1], actual[j], actual[j + 1]) +
                   cost_insert,
               place - row),
      TypoCell(Typo(TypoKind::Delete, j, correct[i]),
               compute_delete_cost(actual[j - 1], correct[i]) + cost_delete,
               place - col)};

  // Matching characters
  if (correct[i] == actual[j]) {
    options.emplace_back(Typo(), cost_sub_skip, place - col - row);
  } else {
    options.emplace_back(Typo(TypoKind::Substitute, j - 1, actual[j]),
                         compute_substitute_cost(correct[i], actual[j]) +
                             cost_sub_skip,
                         place - col - row);
  }

  // Check possible tranposes
  if (transposes.count(place)) {
    const auto transpose_array = transposes.at(place);
    for (size_t n = 0; n < max_tranpose_distance; n++) {
      const auto tcost = transpose_array[n];
      if (tcost != -1) {
        options.emplace_back(Typo(TypoKind::Transpose, j - 2, n + 1),
                             tcost + fill_table(table, transposes, correct,
                                                actual, i - (n + 2),
                                                j - (n + 2)),
                             place - (col * (n + 2)) - row * (n + 2));
      }
    }
  }

  // Select smallest path
  auto min_cell = options[0];
  for (auto i = 1; i < options.size(); i++) {
    if (options[i].cost < min_cell.cost) {
      min_cell = options[i];
    }
  }
  table[place] = min_cell;
  return min_cell.cost;
}

auto find_typos(const TransposeList &transposes, const std::string &correct,
                const std::string &actual) -> TypoStack {
  const auto new_correct = sentinel + correct;
  const auto new_actual = sentinel + actual + sentinel;
  TypoTable data{new_correct.size() * (new_actual.size() - 1)};
  fill_table(data, transposes, new_correct, new_actual, new_correct.size() - 1,
             new_actual.size() - 2);

  std::cout << std::endl;
  for (auto i = 0; i < new_correct.size(); i++) {
    for (auto j = 0; j < (new_actual.size() - 1); j++) {
      std::cout << std::setfill(' ') << std::setw(3)
                << data[i * (new_actual.size() - 1) + j].cost << " ";
    }
    std::cout << std::endl;
  }
  std::cout << data[new_correct.size() * (new_actual.size() - 1) - 1].cost
            << std::endl;

  auto result =
      find_typos(data, new_correct.size() * (new_actual.size() - 1) - 1);
  std::cout << std::endl;
  for (const auto &entry : result) {
    switch (entry.kind) {
    case TypoKind::Insert: {
      std::cout << "Insert " << entry.c << " before " << entry.idx << std::endl;
      break;
    }
    case TypoKind::Delete: {
      std::cout << "Delete " << entry.idx << std::endl;
      break;
    }
    case TypoKind::Substitute: {
      std::cout << "Substitute " << entry.c << " at " << entry.idx << std::endl;
      break;
    }
    case TypoKind::Transpose: {
      std::cout << "Transpose " << entry.idx << "-" << entry.idx + 1
                << std::endl;
      break;
    }
    case TypoKind::None: {
      break;
    }
    }
  }

  return TypoStack{};
}
