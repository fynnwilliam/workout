#include <iostream>
#include <set>
#include <vector>

std::set<int> extract_unique(std::vector<int> const& v) {
  std::set<int> s;
  for (auto elem : v) {
    s.insert(elem);
  }

  return s;
}

int nth_largest_element(auto const& v, int index) {
  std::set<int> s{extract_unique(v)};

  std::size_t count{1};
  for (auto i{begin(s)}; i != end(s); ++i, ++count) {
    if (count == index)
      return *i;
  }

  return -1;
}

int main() {
  std::vector<int> v{1, 3, 2, 17, 18, 8, 19, 22, 2, 10, 11, 11, 133};

  std::cout << nth_largest_element(v, 9) << std::endl;
}