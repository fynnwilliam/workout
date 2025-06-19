#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

bool can_construct(
    std::string s, std::vector<std::string> const& word_bank,
    std::unordered_map<std::string, bool>&& m = {}
) {
  if (m.count(s))
    return m[s];
  if (s.empty())
    return true;

  for (auto const& word : word_bank) {
    if (s.find(word) == 0) {
      if (can_construct(s.substr(word.length()), word_bank, std::move(m))) {
        return m[s] = true;
      }
    }
  }

  return m[s] = false;
}

TEST_CASE("can_construct") {
  std::vector<std::string> v{"a", "p", "ent", "enter", "ot", "o", "t"};
  REQUIRE(can_construct("enterapotentpot", v) == true);
}