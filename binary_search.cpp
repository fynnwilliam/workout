#include <catch2/catch_test_macros.hpp>
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

TEST_CASE("binary_search") {
  using namespace std::string_literals;

  std::vector v{"cat"s, "cow"s, "dog"s, "rabbit"s, "sheep"s};
  const auto v_ptr = v.data();
  const int size = static_cast<int>(v.size());

  REQUIRE(binary_search("cat"s, v_ptr, size) == 0);
}