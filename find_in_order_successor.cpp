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