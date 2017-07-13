#include "typo.hpp"

#include "costs.hpp"

auto find_tranpose(TransposeList &data, const std::string &correct,
                   const std::string &actual) -> void {
  for (auto i = correct.size() - 1; i > 0; --i) {
    for (auto j = correct.size() - 1; j > 1; --j) {
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
        for (auto n = 0; n < max_tranpose_distance; n++) {
          const auto corr = correct[i - n];
          const auto left = actual[j - 1 - n];

          running_cost += compute_transpose_cost(left, curr);
          if (curr == corr) {
            working[n] = running_cost;
            found = true;
          } else {
            working[n] = -1;
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
