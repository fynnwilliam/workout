#include <algorithm>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

struct node {
  node* left = nullptr;
  node* right = nullptr;
  unsigned height = 0;
};

constexpr void compute_height(node&);

constexpr void leaf_height(node& n) {
  n.height = 0;
}

constexpr void left_height(node& n) {
  auto& [left, _, height] = n;
  compute_height(*left);
  height = left->height + 1;
}

constexpr void right_height(node& n) {
  auto& [_, right, height] = n;
  compute_height(*right);
  height = right->height + 1;
}

constexpr void mountain_height(node& n) {
  auto& [left, right, height] = n;
  compute_height(*left);
  compute_height(*right);

  height = std::max(left->height, right->height) + 1;
}

constexpr void compute_height(node& n) {
  auto& [left, right, _] = n;
  !left && !right  ? leaf_height(n)
  : left && right  ? mountain_height(n)
  : left && !right ? left_height(n)
                   : right_height(n);
}

TEST_CASE("height of a default node should be zero(0)") {
  node n;
  compute_height(n);
  REQUIRE(n.height == 0u);
}

namespace {
node a, b, c{&a, &b};
node d, e{&c, &d}, f;
node g, h{&f, &g}, i{&e, &h};
node j, k, l{&j, &k};
node m, n{&l, &m}, o{&i, &n};

node r, s, t{&r, &s};
node u, v{&t, &u}, w;
node x, y{&w, &x}, z{&v, &y};

node p{&o, &z};
} // namespace

TEST_CASE("function calls in fib(7) has a height of 5 when shown as a tree") {
  compute_height(p);
  REQUIRE(p.height == 5u);
}

TEST_CASE("compute_height", "[!benchmark]") {
  BENCHMARK("compute_height(p)") {
    return compute_height(p);
  };
}