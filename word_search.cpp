#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

bool rcontains(std::string_view source, std::string_view word) {
  const auto word_size = word.size();
  for (auto f = source.size() - 1, l = word_size - 1; f >= l; --f) {
    auto i = 0zu;
    for (auto j = f; i < word_size; --j, ++i) {
      if (source[j] != word[i])
        break;
    }

    if (i == word_size)
      return true;
  }

  return false;
}

bool horizontal_search(
    const char* row_ptr, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  for (std::uint32_t r = 0u; r < rows; ++r) {
    std::string_view row_view{row_ptr, columns};
    if (row_view.contains(word) || rcontains(row_view, word))
      return true;
    row_ptr += columns;
  }

  return false;
}

void copy(
    const char* source, std::uint32_t depth, std::uint32_t steps,
    char* destination
) {
  for (std::uint32_t i = 0u; i < depth; ++i) {
    *destination++ = *source;
    source += steps;
  }
}

void rcopy(
    const char* source, std::uint32_t depth, std::uint32_t steps,
    char* destination
) {
  for (std::uint32_t i = 0u; i < depth; ++i) {
    *destination++ = *source;
    source -= steps;
  }
}

bool vertical_search(
    const char* column_ptr, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  char column_data[rows];

  const auto steps = columns;
  while (columns--) {
    copy(column_ptr++, rows, steps, column_data);
    std::string_view column_view{column_data, rows};
    if (column_view.contains(word) || rcontains(column_view, word))
      return true;
  }

  return false;
}

bool slope_search(
    const char* slope_ptr, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  char slope_data[rows];

  auto depth = rows, steps = columns + 1u;
  auto source = slope_ptr;
  for (; depth >= word.size();) {
    copy(source++, depth, steps, slope_data);
    std::string_view slope_view{slope_data, depth--};
    if (slope_view.contains(word) || rcontains(slope_view, word))
      return true;
  }

  depth = rows - 1u, source = slope_ptr + columns;
  for (; depth >= word.size();) {
    copy(source, depth, steps, slope_data);
    std::string_view slope_view{slope_data, depth--};
    if (slope_view.contains(word) || rcontains(slope_view, word))
      return true;
    source += columns;
  }

  depth = rows, source = slope_ptr + columns * (rows - 1u);
  steps = columns - 1;
  for (; depth >= word.size();) {
    rcopy(source++, depth, steps, slope_data);
    std::string_view slope_view{slope_data, depth--};
    if (slope_view.contains(word) || rcontains(slope_view, word))
      return true;
  }

  depth = rows - 1u, source = slope_ptr + columns * (rows - 2u);
  for (; depth >= word.size();) {
    rcopy(source, depth, steps, slope_data);
    std::string_view slope_view{slope_data, depth--};
    if (slope_view.contains(word) || rcontains(slope_view, word))
      return true;
    source -= columns;
  }

  return false;
}

namespace {
std::array<std::array<char, 10>, 10> puzzle{
    std::array{'x', 'x', 'x', 'x', 'd', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'e', 's', 'r', 'e', 'v', 'e', 'r', 'h'},
    std::array{'x', 'x', 'x', 'x', 't', 's', 't', 'x', 'x', 'v'},
    std::array{'x', 'x', 'x', 'n', 'x', 'r', 'x', 'l', 'x', 'e'},
    std::array{'s', 'x', 'a', 'x', 'x', 'e', 'x', 'x', 'i', 'r'},
    std::array{'x', 'l', 'x', 'x', 'x', 'v', 'x', 'x', 'x', 't'},
    std::array{'s', 'x', 'o', 'x', 'x', 'e', 'x', 'x', 'x', 'i'},
    std::array{'x', 'x', 'x', 'p', 'x', 'r', 'x', 'x', 'x', 'c'},
    std::array{'x', 'x', 'x', 'x', 'e', 'v', 'x', 'x', 'x', 'a'},
    std::array{'h', 'o', 'r', 'i', 'z', 'o', 'n', 't', 'a', 'l'}
};
} // namespace

TEST_CASE("horizontal_search") {
  const char* row_ptr = &puzzle[0][0];
  REQUIRE(horizontal_search(row_ptr, 10, 10, "000") == false);
  REQUIRE(horizontal_search(row_ptr, 10, 10, "horizontal") == true);
  REQUIRE(horizontal_search(row_ptr, 10, 10, "hreverse") == true);
}

TEST_CASE("horizontal_search", "[!benchmark]") {
  const char* row_ptr = &puzzle[0][0];
  BENCHMARK("horizontal_search(row_ptr, 10, 10, ooo)") {
    return horizontal_search(row_ptr, 10, 10, "ooo");
  };
}

TEST_CASE("vertical_search") {
  const char* column_ptr = &puzzle[0][0];
  REQUIRE(vertical_search(column_ptr, 10, 10, "000") == false);
  REQUIRE(vertical_search(column_ptr, 10, 10, "vertical") == true);
  REQUIRE(vertical_search(column_ptr, 10, 10, "vreverse") == true);
}

TEST_CASE("vertical_search", "[!benchmark]") {
  const char* column_ptr = &puzzle[0][0];
  BENCHMARK("vertical_search(column_ptr, 10, 10, ooo)") {
    return vertical_search(column_ptr, 10, 10, "ooo");
  };
}

TEST_CASE("slope_search") {
  const char* slope_ptr = &puzzle[0][0];
  REQUIRE(slope_search(slope_ptr, 10, 10, "000") == false);
  REQUIRE(slope_search(slope_ptr, 10, 10, "slope") == true);
  REQUIRE(slope_search(slope_ptr, 10, 10, "slant") == true);
  REQUIRE(slope_search(slope_ptr, 10, 10, "tilted") == true);
}

TEST_CASE("slope_search", "[!benchmark]") {
  const char* slope_ptr = &puzzle[0][0];
  BENCHMARK("slope_search(slope_ptr, 10, 10, ooo)") {
    return slope_search(slope_ptr, 10, 10, "ooo");
  };
}

TEST_CASE("rcontains") {
  std::string_view data{"xxesreverh"};
  REQUIRE(rcontains(data, "revrs") == false);
  REQUIRE(rcontains(data, "reverse") == true);
  REQUIRE(rcontains(data, "hreverse") == true);
}

TEST_CASE("rcontains", "[!benchmark]") {
  std::string_view data{"xxesreverh"};
  BENCHMARK("rcontains(data, ooo)") {
    return rcontains(data, "ooo");
  };
}