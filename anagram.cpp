#include <algorithm>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

auto anagram(std::string a, std::string b) {
  if (a.size() != b.size())
    return false;

  std::ranges::transform(a, a.begin(), [](unsigned char c) -> unsigned char {
    return std::tolower(c);
  });
  std::ranges::transform(b, b.begin(), [](unsigned char c) -> unsigned char {
    return std::tolower(c);
  });

  std::ranges::sort(a);
  std::ranges::sort(b);

  return a == b;
}

auto anagram_(std::string a, std::string b) {
  if (a.size() != b.size())
    return false;

  std::unordered_map<char, std::size_t> map_a;
  auto map_b = map_a;

  for (unsigned char c : a)
    ++map_a[std::tolower(c)];
  for (unsigned char c : b)
    ++map_b[std::tolower(c)];

  return map_a == map_b;
}

TEST_CASE("anagram") {
  REQUIRE(anagram("abcdef", "fedcba") == true);
  REQUIRE(anagram("Listen", "Silent") == true);
  REQUIRE(anagram("Earth", "Heart") == true);
  REQUIRE(anagram("Secure", "Rescue") == true);
  REQUIRE(
      anagram("hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone") ==
      true
  );
}

TEST_CASE("anagram_") {
  REQUIRE(anagram_("abcdef", "fedcba") == true);
  REQUIRE(anagram_("Listen", "Silent") == true);
  REQUIRE(anagram_("Earth", "Heart") == true);
  REQUIRE(anagram_("Secure", "Rescue") == true);
  REQUIRE(
      anagram_("hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone") ==
      true
  );
}

TEST_CASE("anagram", "[!benchmark]") {
  REQUIRE(anagram("Secure", "Rescue") == true);

  BENCHMARK("anagram(hydroxydeoxycorticosterones)") {
    return anagram(
        "hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone"
    );
  };
}

TEST_CASE("anagram_", "[!benchmark]") {
  REQUIRE(anagram_("Secure", "Rescue") == true);

  BENCHMARK("anagram_(hydroxydeoxycorticosterones)") {
    return anagram_(
        "hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone"
    );
  };
}