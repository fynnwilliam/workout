#include <iostream>

constexpr int set_bits(int n) { // Brian Kernighan's approach
  int count{};
  for (; n; count++)
    n &= n - 1;

  return count;
}

constexpr int _set_bits(int n) { // other approach
  int count{};

  while (n) {
    count += n & 1;
    n >>= 1;
  }

  return count;
}

int main() {
  std::cout << set_bits(128) << '\n' << _set_bits(128) << std::endl;
}