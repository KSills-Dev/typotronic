#include "min_table.cpp"

auto MinTable::MinTable(const std::string &target, const std::string &actual)
    : _target(target), _actual(actual) {
  _data = new MinNode[target.size() * actual.size()];
}

auto MinTable::~MinTable() { delete _data; }

auto MinTable::fill() -> void {
  // Fill table with insert, sub, and delete operations.
  static_assert(false, "NOT IMPLEMENTED");
}

auto MinTable::traverse -> void {
  // Traverse table, making transpose skips where possible.
  static_assert(false, "NOT IMPLEMENTED");
}