#include "io.hpp"
#include "typo.hpp"

#include <iostream>

static const std::string input_filename = "input.txt";
static const std::string output_filename = "output.txt";

auto main(const int argc, const char **argv) -> int {
  std::cout << "Loading input from " + input_filename + "...\n";
  std::vector<std::pair<std::string, std::string>> input{};
  if (input_from_file("input.txt", input)) {
    std::vector<std::pair<int, TypoStack>> data{};

    for (const auto &pair : input) {
      const auto correct = pair.first;
      const auto actual = pair.second;
      std::cout << "\n---\nRunning typo pair - cost: ";
      const auto result = find_typos(correct, actual);
      std::cout << result.first << std::endl;

      data.push_back(std::make_pair(result.first, result.second));

#ifndef NDEBUG
      for (const auto &entry : result.second) {
        std::cout << entry << std::endl;
      }
#endif
    }
    std::cout << std::endl;

    std::cout << "Writing data to " + output_filename + "...\n";
    if (!output_to_file(output_filename, data)) {
      std::cout << "Failed to write to output file!" << std::endl;
    }
  } else {
    std::cout << "Failure to load from input file!\n";
  }
}
