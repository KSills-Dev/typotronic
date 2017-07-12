#pragma once

namespace cost {
static const int max_cost = 6;

static const int insert_repeat = 1;
static const int insert_space_ab = 2;
static const int insert_space_ae = 6;
static const int insert_char_as = 6;
static const int insert_char_oh = 5;

static const int delete_repeat = 1;
static const int delete_space = 3;
static const int delete_char_sh = 2;
static const int delete_char_oh = 6;
static const int delete_char_fc = 6;

static const int sub_space_char = 6;
static const int sub_char_sf = 1;
static const int sub_char_oh = 5;

static const int trans_space = 3;
static const int trans_char_sh = 2;
static const int trans_char_oh = 1;
}

auto compute_insert_cost(const char left, const char curr, const char right)
    -> int;

auto compute_delete_cost(const char left, const char curr) -> int;

auto compute_substitute_cost(const char correct, const char actual) -> int;

auto compute_transpose_cost(const char left, const char curr) -> int;