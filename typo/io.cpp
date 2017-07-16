#include "io.hpp"

#include <fstream>
#include <iostream>
#include <string>

auto input_from_file(const std::string &filename,
                     std::vector<std::pair<std::string, std::string>> &data)
    -> bool {
  std::ifstream file{filename};
  if (!file.is_open()) {
    return false;
  }

  std::vector<std::string> lines{};
  for (auto i = 0; !file.eof(); i++) {
    lines.emplace_back();
    std::getline(file, lines[i]);
  }

  const auto n = std::stoi(lines[0]);
  for (auto i = 1; i <= n * 3; i += 3) {
    data.push_back(std::make_pair(lines[i], lines[i + 1]));
  }

  return true;
}

auto output_to_file(const std::string &filename,
                    const std::vector<std::pair<int, TypoStack>> &data)
    -> bool {
  std::ofstream file{filename};
  if (!file.is_open()) {
    return false;
  }

  for (const auto &entry : data) {
    file << entry.first << std::endl;
    for (const auto &typo : entry.second) {
      file << typo << std::endl;
    }
    file << std::endl;
  }
  return true;
}
