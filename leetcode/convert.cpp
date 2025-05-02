#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

std::string convert(const std::string& s, size_t rows) {
  const auto size = s.size();
  if (rows == 1zu || rows >= size)
    return s;

  const auto last_row_index = rows - 1zu;
  const auto initial_steps = last_row_index * 2zu;
  const auto last{cend(s)};

  std::string new_s(size, ' ');

  for (size_t i{}, x{}; i < rows; ++i) {
    auto row_i_steps{2zu * i};
    for (auto j{cbegin(s) + i}; j < last; j += row_i_steps, ++x) {
      new_s[x] = *j;
      row_i_steps = i == 0zu || i == last_row_index
                        ? initial_steps
                        : initial_steps - row_i_steps;
    }
  }

  return new_s;
}

TEST_CASE("convert") {
  REQUIRE(convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
  REQUIRE(convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
  REQUIRE(convert("PAYPALISHIRING", 5) == "PHASIYIRPLIGAN");
}

TEST_CASE("convert", "[!benchmark]") {
  REQUIRE(convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
  REQUIRE(convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
  REQUIRE(convert("PAYPALISHIRING", 5) == "PHASIYIRPLIGAN");

  std::string s(1'000'000, 'a');
  BENCHMARK("convert(std::string s(1'000'000, 'a'), 10)") {
    return convert(s, 10);
  };
}