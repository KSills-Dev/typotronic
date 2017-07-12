#pragma once

#include <vector>

enum class TypoKind { Substitute, Insert, Delete, Transpose };

struct Typo {
  Typo() = default;
  Typo(const TypoKind kind, const size_t idx) : kind(kind), idx(idx), c('\0') {}
  Typo(const TypoKind kind, const size_t idx, const char)
      : kind(kind), idx(idx), c(c) {}

  TypoKind kind;
  size_t idx;
  char c;
};

using TypoStack = std::vector<Typo>;