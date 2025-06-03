#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string_view>

constexpr bool is_palindrome(std::string_view sv) {
  return sv.size() < 2             ? true
         : sv.front() == sv.back() ? is_palindrome(sv.substr(1, sv.size() - 2))
                                   : false;
}

TEST_CASE("is_palindrome") {
  REQUIRE(is_palindrome("kayak") == true);
  REQUIRE(is_palindrome("mountain") == false);
  REQUIRE(is_palindrome("level") == true);
}

TEST_CASE("is_palindrome", "[!benchmark]") {
  std::string s(1'000'000, 'c');
  BENCHMARK("is_palindrome(s)") {
    return is_palindrome(s);
  };
}