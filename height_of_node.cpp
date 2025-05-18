#include <algorithm>

struct node {
  node* left = nullptr;
  node* right = nullptr;
  unsigned height = 0;
};

constexpr void compute_height(node*);

constexpr void leaf_height(node* n) {
  n->height = 0;
}

constexpr void left_height(node* n) {
  auto& [left, _, height] = *n;
  compute_height(left);
  height = left->height + 1;
}

constexpr void right_height(node* n) {
  auto& [_, right, height] = *n;
  compute_height(right);
  height = right->height + 1;
}

constexpr void mountain_height(node* n) {
  auto& [left, right, height] = *n;
  compute_height(left);
  compute_height(right);

  height = std::max(left->height, right->height) + 1;
}

constexpr void compute_height(node* n) {
  auto& [left, right, _] = *n;
  !left && !right  ? leaf_height(n)
  : left && !right ? left_height(n)
  : !left && right ? right_height(n)
                   : mountain_height(n);
}