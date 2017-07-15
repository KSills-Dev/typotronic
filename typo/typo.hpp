#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/**
 @brief Type of a given typo.
 @see Typo
 */
enum class TypoKind { None, Substitute, Insert, Delete, Transpose };

/**
 @brief Output stream operator for TypoKinds.
 @see TypoKind
 */
auto operator<<(std::ostream &stream, const TypoKind kind) -> std::ostream &;

/**
 @brief POD struct for a typo.

 @see find_typos
 @see TypoStack
 @see TypoKind
 */
struct Typo {
  /**
   @brief Default constructor, default to a None typo.
   */
  Typo() : kind(TypoKind::None), idx(0), c('\0'){};

  /**
   @brief Constructs a typo with no c or n element.
   */
  Typo(const TypoKind kind, const size_t idx) : kind(kind), idx(idx), c('\0') {}

  /**
   @brief Constructs a full typo based on the given params.

   @param c Acts as acceptor for either c or n.
   */
  Typo(const TypoKind kind, const size_t idx, const char c)
      : kind(kind), idx(idx), c(c) {}

  /**
   @brief Converts the Typo into a formatted output string.
   */
  auto to_string() const -> std::string;

  TypoKind kind; ///< Type of typo made.
  size_t idx;    ///< Index of typo in actual string.
  union {
    char c; ///< Operated character in Insert, Substitute, or Delete.
    char n; ///< Length of Transpose
  };
};

/**
 @brief Output stream operator for Typos.
 @see Typo
 */
auto operator<<(std::ostream &stream, const Typo typo) -> std::ostream &;

/**
 @brief A cell in a TypoTable

 @see TypoTable
 */
struct TypoCell {
  TypoCell() = default;                      // Default constructor.
  TypoCell(const TypoCell &other) = default; // Default copy.
  auto operator=(const TypoCell &other)
      -> TypoCell & = default; // Default copy.

  /**
   @brief Full Constructor for TypoCell.
   */
  TypoCell(const Typo typo, const int cost, const int parent)
      : typo(typo), cost(cost), parent(parent){};

  /**
   @brief LT comparison for TypoCell, compared on cost member.
   */
  auto operator<(const TypoCell &other) -> bool { return (cost < other.cost); }

  Typo typo;       ///< Typo made moving to the parent cell.
  int cost = 0;    ///< Total cost of typo string at this cell.
  int parent = -1; ///< Parent with the minimum running cost.
};

/**
 @brief Stack of Typo objects.
 @see Typo
 */
using TypoStack = std::vector<Typo>;

/**
 @brief 2D Array of TypoCells.
 @see TypoCell
 */
using TypoTable = std::vector<TypoCell>;

static const int max_tranpose_distance =
    12; ///< Maximum distance transposes may propogate.

/**
 @brief Hashtable for array of Transpose jump costs, indexed by squashed table
 coordinates.
 @see find_transpose
 */
using TransposeList =
    std::unordered_map<int, std::array<int, max_tranpose_distance>>;

/**
 @brief Creates a TransposeList of all possible transposition locations when
 comparing correct and actual.

 @note correct and actual must be prefixed by the sentinel (layout.hpp).

 @see TransposeList
 */
auto find_tranpose(TransposeList &data, const std::string &correct,
                   const std::string &actual) -> void;

/**
 @brief Finds the minimum cost TypoStack for the given correct and actual
 strings.

 @see find_transpose
 @see TypoStack
 */
auto find_typos(const std::string &correct, const std::string &actual)
    -> std::pair<int, TypoStack>;
