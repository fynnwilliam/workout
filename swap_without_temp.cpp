#include <cassert>
#include <concepts>
#include <string>

template <typename T>
  requires std::integral<T> || std::floating_point<T>
void swap(T& a, T& b) {
  a += b;
  b = a - b;
  a -= b;
}

template <typename T>
  requires std::same_as<T, std::string>
void swap(T& a, T& b) {
  a.append(b);
  b = a.substr(0, a.size() - b.size());
  a = a.substr(b.size());
}

int main() {
  char a{'a'};
  char b{'b'};

  ::swap(a, b);
  assert(a == 'b' && b == 'a');

  std::string s1{"world"};
  std::string s2{"hello"};

  ::swap(s1, s2);
  assert(s1 == "hello" && s2 == "world");
}