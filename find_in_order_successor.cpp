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

[[nodiscard]] constexpr node* leftmost_key(node& n) {
  return n.left ? leftmost_key(*n.left) : &n;
}

[[nodiscard]] constexpr node* root_node(node& n) {
  return n.parent ? root_node(*n.parent) : &n;
}

[[nodiscard]] constexpr bool is_left_alligned(node& n) {
  auto& [parent, _, _, _] = n;
  return parent && &n == parent->left;
}

[[nodiscard]] constexpr node* climb(node& n) {
  node* root = root_node(n);
  return *root > n ? root : nullptr;
}

[[nodiscard]] constexpr node* in_order_successor(node& n) {
  auto& [parent, _, right, _] = n;
  if (right != nullptr) {
    return leftmost_key(*right);
  }
  return is_left_alligned(n) ? parent : climb(n);
}

/*
            23
           /  \
          11   25
         /  \
        7    15
            /  \
           13  17
*/

TEST_CASE("in_order_successor") {
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

  REQUIRE(in_order_successor(e) == &g);
  REQUIRE(in_order_successor(b) == &f);
  REQUIRE(in_order_successor(a) == &c);
  REQUIRE(in_order_successor(d) == &b);
  REQUIRE(in_order_successor(f) == &e);
  REQUIRE(in_order_successor(g) == &a);
  REQUIRE(in_order_successor(c) == nullptr);
}