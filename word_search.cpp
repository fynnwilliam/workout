#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

bool horizontal_search(
    const char* row_ptr, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  for (std::uint32_t r = 0u; r < rows; ++r) {
    std::string_view row_view{row_ptr, columns};
    if (row_view.contains(word))
      return true;
    row_ptr += columns;
  }

  return false;
}

void copy(
    const char* source, std::uint32_t rows, std::uint32_t steps,
    char* destination
) {
  for (std::uint32_t i = 0u; i < rows; ++i) {
    *destination++ = *source;
    source += steps;
  }
}

bool vertical_search(
    const char* column_ptr, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  char column_data[rows];

  for (std::uint32_t c = 0u; c < columns; ++c) {
    copy(column_ptr++, rows, columns, column_data);
    std::string_view column_view{column_data, rows};
    if (column_view.contains(word))
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
  for (std::uint32_t c = 0u; c < columns && depth >= word.size(); ++c) {
    copy(source++, depth, steps, slope_data);
    std::string_view slope_view{slope_data, depth--};
    if (slope_view.contains(word))
      return true;
  }

  depth = rows - 1u, source = slope_ptr + columns;
  for (std::uint32_t r = 1u; r < rows && depth >= word.size(); ++r) {
    copy(source, depth, steps, slope_data);
    std::string_view slope_view{slope_data, depth--};
    if (slope_view.contains(word))
      return true;
    source += columns;
  }

  return false;
}

namespace {
std::array<std::array<char, 10>, 10> puzzle{
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'o', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o'},
    std::array{'x', 'o', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o'},
    std::array{'x', 'x', 'o', 'x', 'x', 'x', 'x', 'o', 'o', 'o'}
};
} // namespace

TEST_CASE("horizontal_search") {
  const char* row_ptr = &puzzle[0][0];
  REQUIRE(horizontal_search(row_ptr, 10, 10, "000") == false);
  REQUIRE(horizontal_search(row_ptr, 10, 10, "ooo") == true);
}

TEST_CASE("horizontal_search", "[!benchmark]") {
  const char* row_ptr = &puzzle[0][0];
  BENCHMARK("horizontal_search(row_ptr, 10, 10, ooo) == true)") {
    return horizontal_search(row_ptr, 10, 10, "ooo");
  };
}

TEST_CASE("vertical_search") {
  const char* column_ptr = &puzzle[0][0];
  REQUIRE(vertical_search(column_ptr, 10, 10, "000") == false);
  REQUIRE(vertical_search(column_ptr, 10, 10, "ooo") == true);
}

TEST_CASE("vertical_search", "[!benchmark]") {
  const char* column_ptr = &puzzle[0][0];
  BENCHMARK("vertical_search(column_ptr, 10, 10, ooo) == true)") {
    return vertical_search(column_ptr, 10, 10, "ooo");
  };
}

TEST_CASE("slope_search") {
  const char* slope_ptr = &puzzle[0][0];
  REQUIRE(slope_search(slope_ptr, 10, 10, "000") == false);
  REQUIRE(slope_search(slope_ptr, 10, 10, "ooo") == true);
}

TEST_CASE("slope_search", "[!benchmark]") {
  const char* slope_ptr = &puzzle[0][0];
  BENCHMARK("slope_search(slope_ptr, 10, 10, ooo) == true)") {
    return slope_search(slope_ptr, 10, 10, "ooo");
  };
}