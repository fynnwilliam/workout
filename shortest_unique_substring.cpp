#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string_view>
#include <vector>

std::string check_sub(std::string_view s, const auto& arr) {
  for (auto const& x : arr) {
    if (s.find(x) == std::string_view::npos)
      return std::string{};
  }

  return std::string{s};
}

std::string smallest_substr(std::string_view s, auto const& arr) {
  const auto arr_size = arr.size();
  if (arr_size > s.size())
    return std::string{};

  std::string arr_str(arr_size, ' ');
  std::memcpy(arr_str.data(), arr.data(), arr_size);

  return s.find(arr_str) == std::string_view::npos ? std::string{} : arr_str;
}

TEST_CASE("smallest_substr") {
  using namespace std::string_literals;
  REQUIRE(
      smallest_substr("hippopotamus", std::vector{'o', 't', 'a'}) == "ota"s
  );
}

TEST_CASE("smallest_substr", "[!benchmark]") {
  std::string s(1'000'000, ' ');
  BENCHMARK("smallest_substr(s, arr)") {
    return smallest_substr(s, std::vector{'o', 't', 'a'});
  };
}