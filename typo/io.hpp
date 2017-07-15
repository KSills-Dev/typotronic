#pragma once

#include "typo.hpp"

#include <string>
#include <vector>

/**
 @brief Imports a string list from the given file.

 The first line in the file should specify the number of problem instances,
 followed by newline delimited pairs of "correct\ntypo" pairs.

 @return True on successful import, false otherwise.
 */
auto input_from_file(const std::string &filename,
                     std::vector<std::pair<std::string, std::string>> &data)
    -> bool;

/**
 @brief Exports the string form of data (delimited by newlines) to the given
 file.

 @return True on successful export, false otherwise.
 */
auto output_to_file(const std::string &filename,
                    const std::vector<std::pair<int, TypoStack>> &data) -> bool;
