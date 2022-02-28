#include <fmt/format.h>
#include <string>

std::string to_binary(int d) {
  return !d ? std::string{'0'} : to_binary(d / 2) + std::to_string(d % 2);
}

int main() { fmt::print("{}\n", to_binary(233)); }