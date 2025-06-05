#include <catch2/catch_test_macros.hpp>
#include <string>

std::string reverse_str(std::string s) {
  return s.empty() ? std::string{} : reverse_str(s.substr(1)) + s[0];
}

TEST_CASE("reverse_str") {
  using namespace std::string_literals;
  REQUIRE(reverse_str("perception") == "noitpecrep"s);
  REQUIRE(reverse_str("require") == "eriuqer"s);
  REQUIRE(reverse_str("reverse") == "esrever"s);
  REQUIRE(reverse_str("etarelecca") == "accelerate"s);
}