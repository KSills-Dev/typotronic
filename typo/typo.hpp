#pragma once

#include <unordered_map>
#include <vector>

enum class TypoKind { None, Substitute, Insert, Delete, Transpose };

struct Typo {
  Typo() : kind(TypoKind::None), idx(0), c('\0'){};
  Typo(const TypoKind kind, const size_t idx) : kind(kind), idx(idx), c('\0') {}
  Typo(const TypoKind kind, const size_t idx, const char c)
      : kind(kind), idx(idx), c(c) {}

  TypoKind kind;
  size_t idx;
  union {
    char c;
    char n;
  };
};

struct TypoCell {
  TypoCell() = default;
  TypoCell(const Typo typo, const int cost, const int parent)
      : typo(typo), cost(cost), parent(parent){};
  Typo typo;
  int cost = 0;
  int parent = -1;
};

using TypoStack = std::vector<Typo>;
using TypoTable = std::vector<TypoCell>;

static const int max_tranpose_distance = 12;

using TransposeList =
    std::unordered_map<int, std::array<int, max_tranpose_distance>>;

auto find_tranpose(TransposeList &data, const std::string &correct,
                   const std::string &actual) -> void;

auto find_typos(const std::string &correct, const std::string &actual)
    -> std::pair<int, TypoStack>;
