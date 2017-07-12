#include "costs.hpp"
#include "typo.hpp"

#include <iostream>

auto reduce_typos(const std::vector<Typo> &t) -> int {
  auto result = 0;
  for (const auto &v : t) {
    result += v.cost;
  }
  return result;
}

auto do_stuff(const std::string &correct, const std::string &typo)
    -> std::vector<Typo> {
  if (correct.size() == 1 && typo.size() == 2) {
    return std::vector<Typo>();
  }

  if (correct.size() == 1) {
    auto result = do_stuff(correct, typo.substr(0, typo.size() - 1));
    result.emplace_back(TypoClass::Insert,
                        compute_insert_cost(typo[typo.size() - 3],
                                            typo[typo.size() - 2], typo.back()),
                        typo.size() - 3, typo);
    return result;
  }
  if (typo.size() == 2) {
    auto result = std::vector<Typo>(correct.size() - 1);
    for (auto &v : result) {
      v.kind = TypoClass::Delete;
      v.cost = 6;
      v.idx = -1;
      v.typo = typo;
    }
    return result;
  }

  auto options = std::vector<std::vector<Typo>>();
  auto corr = correct.back();
  auto left = typo[typo.size() - 3];
  auto curr = typo[typo.size() - 2];
  auto right = typo.back();

  if (corr == curr) {
    return do_stuff(correct.substr(0, correct.size() - 1),
                    typo.substr(0, typo.size() - 1));
  }

  auto substitute = do_stuff(correct.substr(0, correct.size() - 1),
                             typo.substr(0, typo.size() - 1));
  substitute.emplace_back(TypoClass::Substitute,
                          compute_substitute_cost(corr, curr), typo.size() - 3,
                          typo);
  options.push_back(substitute);

  auto insert = do_stuff(correct, typo.substr(0, typo.size() - 1));
  insert.emplace_back(TypoClass::Insert, compute_insert_cost(left, curr, right),
                      typo.size() - 2, typo);
  options.push_back(insert);

  auto del = do_stuff(correct.substr(0, correct.size() - 1), typo);
  del.emplace_back(TypoClass::Delete, compute_delete_cost(curr, corr),
                   typo.size() - 1, typo);
  options.push_back(del);

  if (corr == left) {
    auto traveller = curr;
    auto idx =

        auto transpose =
            do_stuff(correct.substr(0, correct.size() - 1), new_string);
    transpose.emplace_back(TypoClass::Transpose,
                           compute_transpose_cost(left, curr), typo.size() - 3,
                           typo);
    options.push_back(transpose);
  }

  auto mini = 0;
  auto minv = reduce_typos(options[0]);
  for (auto i = 1; i < options.size(); i++) {
    const auto cost = reduce_typos(options[i]);
    if (cost < minv) {
      mini = i;
      minv = cost;
    }
  }
  return options[mini];
}

auto prep_stuff(const std::string &correct, const std::string &actual)
    -> std::vector<Typo> {
  return do_stuff("\0" + correct, "\0" + actual + '\0');
}

auto main(const int argc, const char **argv) -> int {
  std::cout << "Still just a stub!\n";
}
