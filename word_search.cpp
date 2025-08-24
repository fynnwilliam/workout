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

void update_column_data(
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
    update_column_data(column_ptr++, rows, columns, column_data);
    std::string_view column_view{column_data, rows};
    if (column_view.contains(word))
      return true;
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
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o', 'o', 'o'}
};
} // namespace

TEST_CASE("horizontal_search") {
  const auto row_ptr = &puzzle[0][0];
  REQUIRE(horizontal_search(row_ptr, 10, 10, "000") == false);
  REQUIRE(horizontal_search(row_ptr, 10, 10, "ooo") == true);
}

TEST_CASE("horizontal_search", "[!benchmark]") {
  const auto row_ptr = &puzzle[0][0];
  BENCHMARK("horizontal_search(row_ptr, 10, 10, ooo) == true)") {
    return horizontal_search(row_ptr, 10, 10, "ooo");
  };
}

TEST_CASE("vertical_search") {
  auto column_ptr = &puzzle[0][0];
  REQUIRE(vertical_search(column_ptr, 10, 10, "000") == false);
  REQUIRE(vertical_search(column_ptr, 10, 10, "ooo") == true);
}

TEST_CASE("vertical_search", "[!benchmark]") {
  auto column_ptr = &puzzle[0][0];
  BENCHMARK("vertical_search(column_ptr, 10, 10, ooo) == true)") {
    return vertical_search(column_ptr, 10, 10, "ooo");
  };
}