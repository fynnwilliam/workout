#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

bool horizontal_search(
    std::unique_ptr<const char*>& puzzle_ptr, std::uint32_t rows,
    std::uint32_t columns, std::string_view word
) {
  auto head = *puzzle_ptr.get();
  for (std::uint32_t r = 0u; r < rows; ++r) {
    std::string_view row_view{head, columns};
    if (row_view.contains(word))
      return true;
    head += columns;
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
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
    std::array{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o', 'o', 'o'}
};
} // namespace

TEST_CASE("horizontal_search") {
  auto puzzle_ptr = std::make_unique<const char*>(&puzzle[0][0]);
  REQUIRE(horizontal_search(puzzle_ptr, 10, 10, "000") == false);
  REQUIRE(horizontal_search(puzzle_ptr, 10, 10, "ooo") == true);
}

TEST_CASE("horizontal_search", "[!benchmark]") {
  auto puzzle_ptr = std::make_unique<const char*>(&puzzle[0][0]);
  BENCHMARK("horizontal_search(puzzle_ptr, 10, 10, ooo) == true)") {
    return horizontal_search(puzzle_ptr, 10, 10, "ooo");
  };
}