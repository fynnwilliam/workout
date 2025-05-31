#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

template <typename T>
int binary_search(T elem, T const* const v, int const& size) noexcept {
  int left{};
  int right{size - 1};

  while (left <= right) {
    int middle = left + (right - left) / 2;

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
  REQUIRE(binary_search("cow"s, v_ptr, size) == 1);
  REQUIRE(binary_search("dog"s, v_ptr, size) == 2);
  REQUIRE(binary_search("rabbit"s, v_ptr, size) == 3);
  REQUIRE(binary_search("sheep"s, v_ptr, size) == 4);
  REQUIRE(binary_search("unknown"s, v_ptr, size) == -1);
}

TEST_CASE("binary_search", "[!benchmark]") {
  using namespace std::string_literals;
  std::vector v{"cat"s, "cow"s, "dog"s, "rabbit"s, "sheep"s};
  const int size = static_cast<int>(v.size());

  BENCHMARK("binary_search(unknown, v_ptr, size)") {
    return binary_search("unknown"s, std::data(v), size);
  };
}