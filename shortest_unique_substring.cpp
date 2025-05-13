#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

std::string check_sub(std::string const& s, auto& arr) {
  for (auto const& x : arr) {
    if (s.find(x) == std::string::npos)
      return std::string{};
  }

  return s;
}

std::string smallest_substr(std::string const& s, auto const& arr) {
  if (arr.size() > s.size())
    return std::string{};

  for (std::size_t i{}; i <= s.size() - arr.size(); ++i) {
    std::string sub_str = check_sub(s.substr(i, arr.size()), arr);
    if (!sub_str.empty())
      return sub_str;
  }

  return std::string{};
}

TEST_CASE("smallest_substr") {
  using namespace std::string_literals;
  REQUIRE(
      smallest_substr("hippopotamus", std::vector{'o', 't', 'a'}) == "ota"s
  );
}

TEST_CASE("smallest_substr", "[!benchmark]") {
  BENCHMARK("smallest_substr(s, arr)") {
    return smallest_substr("hippopotamus", std::vector{'o', 't', 'a'});
  };
}