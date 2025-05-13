#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

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

int main() {
  std::vector v{'o', 't', 'a'};
  std::cout << smallest_substr("hippopotamus", v) << std::endl;
}