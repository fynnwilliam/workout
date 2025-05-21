#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

struct node {
  node* parent = nullptr;
  node* left = nullptr;
  node* right = nullptr;
  int value = 0;
};

[[nodiscard]] constexpr bool operator>(const node& lhs, const node& rhs) {
  return lhs.value > rhs.value;
}

template <typename node_t> using n_ptr = std::remove_reference_t<node_t>*;

[[nodiscard]] constexpr auto leftmost_key(auto& n) -> n_ptr<decltype(n)> {
  return n.left ? leftmost_key(*n.left) : &n;
}

[[nodiscard]] constexpr auto root_node(auto& n) -> n_ptr<decltype(n)> {
  return n.parent ? root_node(*n.parent) : &n;
}

[[nodiscard]] constexpr bool is_left_alligned(const node& n) {
  auto& [parent, _, _, _] = n;
  return parent && &n == parent->left;
}

[[nodiscard]] constexpr auto climb(auto& n) -> n_ptr<decltype(n)> {
  n_ptr<decltype(n)> root = root_node(n);
  return *root > n ? root : nullptr;
}

[[nodiscard]] constexpr auto inorder_successor(auto& n) -> n_ptr<decltype(n)> {
  auto& [parent, _, right, _] = n;
  if (right != nullptr) {
    return leftmost_key(*right);
  }
  return is_left_alligned(n) ? parent : climb(n);
}

/*
            20
           /  \
          8   22
         /  \
        4    12
            /  \
           10  14
*/

TEST_CASE("inorder_successor") {
  node a{.value = 20};
  node b{.parent = &a, .value = 8}, c{.parent = &a, .value = 22};
  a.left = &b;
  a.right = &c;
  node d{.parent = &b, .value = 4}, e{.parent = &b, .value = 12};
  b.left = &d;
  b.right = &e;
  node f{.parent = &e, .value = 10}, g{.parent = &e, .value = 14};
  e.left = &f;
  e.right = &g;

  REQUIRE(inorder_successor(e) == &g);
  REQUIRE(inorder_successor(b) == &f);
  REQUIRE(inorder_successor(a) == &c);
  REQUIRE(inorder_successor(d) == &b);
  REQUIRE(inorder_successor(f) == &e);
  REQUIRE(inorder_successor(g) == &a);
  REQUIRE(inorder_successor(c) == nullptr);
}

TEST_CASE("inorder_successor", "[!benchmark]") {
  node a{.value = 23};
  node b{.parent = &a, .value = 11}, c{.parent = &a, .value = 25};
  a.left = &b;
  a.right = &c;
  node d{.parent = &b, .value = 7}, e{.parent = &b, .value = 15};
  b.left = &d;
  b.right = &e;
  node f{.parent = &e, .value = 13}, g{.parent = &e, .value = 17};
  e.left = &f;
  e.right = &g;

  BENCHMARK("inorder_successor(g)") {
    return inorder_successor(g);
  };
}