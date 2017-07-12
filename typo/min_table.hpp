#pragma once

#include "typo.hpp"

#include <string>
#include <vector>

struct MinNode {
  int cost;
  std::pair<size_t, size_t> parent;
};

class MinTable {
  MinTable() = delete;
  MinTable(const std::string &target, const std::string &actual);

  ~MinTable();

  auto fill() -> void;

  auto traverse() const -> std::vector<Typo>;

private:
  const std::string _target;
  const std::string _actual;
  MinNode *_data;
};