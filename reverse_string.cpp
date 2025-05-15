#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

std::string reverse_str(std::string s) {
  for (char* i = s.data(), *j = i + s.size() - 1; i < j; ++i, --j)
    std::swap(*i, *j);

  return s;
}

TEST_CASE("reverse_str") {
  using namespace std::string_literals;
  REQUIRE(reverse_str("how are you doing?") == "?gniod uoy era woh"s);
  REQUIRE(reverse_str("?gniod uoy era woh") == "how are you doing?"s);
  REQUIRE(reverse_str("how_are_you_doing?") == "?gniod_uoy_era_woh"s);
}

TEST_CASE("reverse_str", "[!benchmark]") {
  std::string s(1'000'000, ' ');
  BENCHMARK("reverse_str(s)") {
    return reverse_str(s);
  };
}