#pragma once

#include <unordered_map>
#include <vector>

enum class TypoKind { Substitute, Insert, Delete, Transpose };

struct Typo {
  Typo() = default;
  Typo(const TypoKind kind, const size_t idx) : kind(kind), idx(idx), c('\0') {}
  Typo(const TypoKind kind, const size_t idx, const char c)
      : kind(kind), idx(idx), c(c) {}

  TypoKind kind;
  size_t idx;
  char c;
};

using TypoStack = std::vector<Typo>;

static const int max_tranpose_distance = 12;

using TransposeList =
    std::unordered_map<int, std::array<int, max_tranpose_distance>>;

auto find_tranpose(TransposeList &data, const std::string &correct,
                   const std::string &actual) -> void;
