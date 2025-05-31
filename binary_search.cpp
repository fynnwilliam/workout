#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
int binary_search(T elem, T const* const v, int const& size) noexcept {
  int left{};
  int right{size - 1};

  while (left <= right) {
    int middle{(left + right) / 2};

    if (v[middle] == elem)
      return middle;
    else if (v[middle] < elem)
      left = ++middle;
    else
      right = --middle;
  }

  return -1;
}

template <typename T> void print(T const& v) noexcept {
  std::cout << "[ ";

  for (auto const& item : v)
    std::cout << item << ' ';

  std::cout << "]\n";
}

void verify(int const& index) noexcept {
  if (index == -1)
    std::cout << "element not found, kindly check for typos" << std::endl;
  else
    std::cout << "element found at index " << index << std::endl;
}

int main() {
  std::vector<std::string> v{"cat", "dog", "cow", "sheep", "rabbit"};

  std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a < b; });
  print(v);

  std::cout << "please enter an element to search: ";
  std::string elem{};
  std::getline(std::cin, elem);

  int index = binary_search(elem, v.data(), v.size());

  verify(index);
}