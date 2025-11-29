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
    const auto& data, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  while (rows--) {
    std::string_view row_view{&data[rows][columns], columns};
    if (row_view.contains(word) || rcontains(row_view, word))
      return true;
  }

  return false;
}

void xcopy(const char* source, uint32_t depth, auto steps, char* destination) {
  while (depth--) {
    *destination++ = *source;
    source += steps;
  }
}

bool vertical_search(
    const auto& data, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  std::vector<char> column_data(rows);

  const auto steps = columns;
  while (columns--) {
    xcopy(&data[0][columns], rows, steps, column_data.data());
    std::string_view column_view{column_data.data(), rows};
    if (column_view.contains(word) || rcontains(column_view, word))
      return true;
  }

  return false;
}

bool slope_search(
    const auto& data, std::uint32_t rows, std::uint32_t columns,
    std::string_view word
) {
  auto word_found = [&word, slope_data = std::vector<char>(rows)](
                        const char* source, auto n, uint32_t depth, auto steps
                    ) mutable {
    auto count = depth >= word.size() ? depth - word.size() + 1 : 0;
    while (count--) {
      xcopy(source, depth, steps, slope_data.data());
      std::string_view slope_view{slope_data.data(), depth--};
      if (slope_view.contains(word) || rcontains(slope_view, word))
        return true;
      source += n;
    }

    return false;
  };

  const int rstep = -static_cast<int>(columns - 1);
  return word_found(&data[0][0], 1, rows, columns + 1) ||
         word_found(&data[1][0], columns, rows - 1, columns + 1) ||
         word_found(&data[rows - 1][0], 1, rows, rstep) ||
         word_found(&data[rows - 2][0], -int(columns), rows - 1, rstep);
}

bool word_search(const auto& data, std::string_view word) {
  const auto rows = data.size();
  if (rows == 0)
    return false;

  const auto columns = data[0].size();

  return horizontal_search(data, rows, columns, word) ||
         vertical_search(data, rows, columns, word) ||
         slope_search(data, rows, columns, word);
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
  REQUIRE(horizontal_search(puzzle, 10, 10, "000") == false);
  REQUIRE(horizontal_search(puzzle, 10, 10, "horizontal") == true);
  REQUIRE(horizontal_search(puzzle, 10, 10, "hreverse") == true);
}

TEST_CASE("horizontal_search", "[!benchmark]") {
  BENCHMARK("horizontal_search(puzzle, 10, 10, ooo)") {
    return horizontal_search(puzzle, 10, 10, "ooo");
  };
}

TEST_CASE("vertical_search") {
  REQUIRE(vertical_search(puzzle, 10, 10, "000") == false);
  REQUIRE(vertical_search(puzzle, 10, 10, "vertical") == true);
  REQUIRE(vertical_search(puzzle, 10, 10, "vreverse") == true);
}

TEST_CASE("vertical_search", "[!benchmark]") {
  BENCHMARK("vertical_search(puzzle, 10, 10, ooo)") {
    return vertical_search(puzzle, 10, 10, "ooo");
  };
}

TEST_CASE("slope_search") {
  REQUIRE(slope_search(puzzle, 10, 10, "000") == false);
  REQUIRE(slope_search(puzzle, 10, 10, "slope") == true);
  REQUIRE(slope_search(puzzle, 10, 10, "slant") == true);
  REQUIRE(slope_search(puzzle, 10, 10, "tilted") == true);
}

TEST_CASE("slope_search", "[!benchmark]") {
  BENCHMARK("slope_search(puzzle, 10, 10, ooo)") {
    return slope_search(puzzle, 10, 10, "ooo");
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

TEST_CASE("word_search") {
  REQUIRE(word_search(puzzle, "000") == false);
  REQUIRE(word_search(puzzle, "horizontal") == true);
  REQUIRE(word_search(puzzle, "vertical") == true);
  REQUIRE(word_search(puzzle, "tilted") == true);
}

TEST_CASE("word_search", "[!benchmark]") {
  BENCHMARK("word_search(puzzle, ooo)") {
    return word_search(puzzle, "ooo");
  };
}