#include <catch2/catch_test_macros.hpp>
#include <string_view>

constexpr bool is_palindrome(std::string_view sv) {
  return sv.size() < 2             ? true
         : sv.front() == sv.back() ? is_palindrome(sv.substr(1, sv.size() - 2))
                                   : false;
}

TEST_CASE("is_palindrome") {
  REQUIRE(is_palindrome("kayak") == true);
}