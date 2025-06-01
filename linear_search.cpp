#include <iostream>
#include <limits>

template <typename T>
int linear_search(T elem, T const* v, int const& size) noexcept {
  for (int i = 0; i < size; ++i) {
    if (v[i] == elem)
      return i;
  }

  return -1;
}

template <typename T> void print(T const& v) noexcept {
  std::cout << '[';

  for (auto const& item : v)
    std::cout << item << ' ';

  std::cout << "]\n";
}

void verify(int const& index) noexcept {
  if (index == -1)
    std::cout << "element not found\n";
  else
    std::cout << "element found at index " << index << std::endl;
}

int main() {
  int arr[]{3, 4, 33, 9, 23, 99};
  print(arr);

  std::cout << "please enter an element to search: ";
  int elem{};
  std::cin >> elem;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  int index = linear_search(elem, arr, 6);

  verify(index);
}