#include <iostream>

int _atoi(std::string_view s) {
  int index{};
  int sign{1};

  if (s[index] == '-') {
    sign = -1;
    ++index;
  }

  int res{};
  for (; s[index] != '\0'; ++index) {
    if (s[index] < '0' || s[index] > '9')
      break;

    res = res * 10 + s[index] - '0';
  }

  return res * sign;
}

int main() {
  std::cout << _atoi("-135d3") << '\n';
  std::cout << std::atoi("-135d3") << std::endl;
}