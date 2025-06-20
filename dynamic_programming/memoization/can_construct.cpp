#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

bool can_construct(
    std::string s, std::vector<std::string> const& word_bank,
    std::unordered_map<std::string, bool>& m
) {
  if (m.count(s))
    return m[s];
  if (s.empty())
    return true;

  for (auto const& word : word_bank) {
    if (s.find(word) == 0) {
      if (can_construct(s.substr(word.length()), word_bank, m)) {
        return m[s] = true;
      }
    }
  }

  return m[s] = false;
}

TEST_CASE("can_construct") {
  std::unordered_map<std::string, bool> a, b, c, d;
  REQUIRE(
      can_construct("enterapotentpot", {"a", "p", "ent", "er", "ot"}, a) == true
  );
  REQUIRE(can_construct("skateboard", {"bo", "rd", "ate", "ska"}, b) == false);
  REQUIRE(
      can_construct("abcdef", {"ab", "abc", "cd", "def", "abcd"}, c) == true
  );
  REQUIRE(can_construct("aaaaaaaaaaz", {"a", "aa", "aaa", "aaaa"}, d) == false);
}