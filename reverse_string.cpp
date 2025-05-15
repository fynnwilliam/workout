#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

std::string reverse_str(std::string s) {
  std::string reversed{s};

  std::size_t size = s.size();

  for (char const& c : s)
    reversed[--size] = c;

  return reversed;
}

TEST_CASE("reverse_str") {
  using namespace std::string_literals;
  REQUIRE(reverse_str("how are you doing?") == "?gniod uoy era woh"s);
}

TEST_CASE("reverse_str", "[!benchmark]") {
  std::string s(1'000'000, ' ');
  BENCHMARK("reverse_str(s)") {
    return reverse_str(s);
  };
}