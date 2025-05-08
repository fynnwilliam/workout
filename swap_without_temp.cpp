#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <concepts>
#include <string>

namespace swt {
template <typename number>
  requires std::integral<number> || std::floating_point<number>
void swap(number& a, number& b) {
  a += b;
  b = a - b;
  a -= b;
}

template <typename str_t>
  requires std::same_as<str_t, std::string>
void swap(str_t& a, str_t& b) {
  a.append(b);
  b = a.substr(0, a.size() - b.size());
  a = a.substr(b.size());
}
} // namespace swt

TEST_CASE("swap(char, char)") {
  char a{'a'};
  char b{'b'};

  swt::swap(a, b);
  REQUIRE(a == 'b');
  REQUIRE(b == 'a');
}

TEST_CASE("swap(std::string, std::string)") {
  std::string s1{"world"};
  std::string s2{"hello"};

  swt::swap(s1, s2);
  REQUIRE(s1 == "hello");
  REQUIRE(s2 == "world");
}

TEST_CASE("swap", "[!benchmark]") {
  std::string s1{"world"};
  std::string s2{"hello"};

  swt::swap(s1, s2);

  BENCHMARK("swt::swap(s1, s2)") {
    return swt::swap(s1, s2);
  };
}