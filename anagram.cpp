#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

auto anagram(std::string a, std::string b) {
  if (a.size() != b.size())
    return false;

  std::sort(begin(a), end(a));
  std::sort(begin(b), end(b));

  return a == b;
}

auto anagram_(std::string a, std::string b) {
  if (a.size() != b.size())
    return false;

  std::unordered_map<char, std::size_t> map_a;
  auto map_b = map_a;

  for (auto const& c : a)
    ++map_a[c];
  for (auto const& c : b)
    ++map_b[c];

  return map_a == map_b;
}

TEST_CASE("anagram") { REQUIRE(anagram("abcdef", "fedcba") == true); }

TEST_CASE("anagram_") { REQUIRE(anagram_("abcdef", "fedcba") == true); }