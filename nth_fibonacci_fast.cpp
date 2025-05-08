#include <cassert>
#include <cstddef>
#include <cstdint>

const auto fib_fast = [](uint8_t n) {
  assert(n < 94);
  if (n == 0 || n > 93)
    return 0zu;

  size_t f1 = 1, f2 = 1, result = 1;
  while (n-- > 2) {
    result = f1 + f2;
    f1 = f2;
    f2 = result;
  }

  return result;
};