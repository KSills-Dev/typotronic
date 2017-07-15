#pragma once

/**
 @brief Constants for typo costs.
 */
namespace cost {
static const int max_cost = 6; ///< Max possible cost of an operation.

static const int insert_repeat = 1; ///< Insert a repeated character.
static const int insert_space_ab =
    2; ///< Insert space after character on the bottom row.
static const int insert_space_ae = 6; ///< Insert space after any character.
static const int insert_char_bs = 6;  ///< Insert character before space.
static const int insert_char_oh = 5;  ///< Insert character after other hand.

static const int delete_repeat = 1;  ///< Delete a repeated chraacter.
static const int delete_space = 3;   ///< Delete a space.
static const int delete_char_sh = 2; ///< Delete a character on the same hand.
static const int delete_char_oh = 6; ///< Delete a character after other hand.
static const int delete_char_fc = 6; ///< Delete first character in string.

static const int sub_space = 6; ///< Substitute space.
static const int sub_char_sf =
    1; ///< Substitute a character from other hand, same finger.
static const int sub_char_oh =
    5; ///< Substitute a character from other hand, different finger.

static const int trans_space = 3;   ///< Transpose a space.
static const int trans_char_sh = 2; ///< Transpace a character on the same hand.
static const int trans_char_oh = 1; ///< Transpose a character on other hand.
}

/**
 @brief Computes the cost of an insert operation.
 @param left Character left of the current character in the actual string.
 @param curr Current character of the actual string (being inserted).
 @param right Character right of the current character in the actual string.
 */
auto compute_insert_cost(const char left, const char curr, const char right)
    -> int;

/**
 @brief Computes the cost of a delete operation.
 @param left Character left of the current character in the actual string.
 @param corr Current character of the correct string (being deleted).
 */
auto compute_delete_cost(const char left, const char corr) -> int;

/**
 @brief Computes the cost of a substitution.
 @param correct Character being replaced in the correct string.
 @param actual Character replacing with from the actual string.
 */
auto compute_substitute_cost(const char correct, const char actual) -> int;

/**
 @brief Computes the cost of a transposition.
 @param left Character left of the current character in the actual string.
 @param curr Current character of the correct string.
 */
auto compute_transpose_cost(const char left, const char curr) -> int;

#ifdef TESTS_ENABLED

/**
 @brief Tests compute_insert_cost.
 */
auto cost_test_compute_insert() -> bool;

/**
 @brief Tests compute_delete_cost.
 */
auto cost_test_compute_delete() -> bool;

/**
 @brief Tests compute_substitute_cost.
 */
auto cost_test_compute_substitute() -> bool;

/**
 @brief Tests compute_transpose_cost.
 */
auto cost_test_compute_transpose() -> bool;

#endif
