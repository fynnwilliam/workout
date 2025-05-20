struct node {
  node* parent = nullptr;
  node* left = nullptr;
  node* right = nullptr;
  int value = 0;
};

constexpr bool operator>(const node& lhs, const node& rhs) noexcept {
  return lhs.value > rhs.value;
}

constexpr node* leftmost_key(node& n) {
  return n.left ? leftmost_key(*n.left) : &n;
}

constexpr node* root_node(node& n) {
  return n.parent ? root_node(*n.parent) : &n;
}

constexpr bool is_left_alligned(node& n) {
  auto& [parent, _, _, _] = n;
  return parent && &n == parent->left;
}

constexpr node* climb(node& n) {
  node* root = root_node(n);
  return *root > n ? root : nullptr;
}

constexpr node* in_order_successor(node& n) {
  auto& [parent, _, right, _] = n;
  if (right != nullptr) {
    return leftmost_key(*right);
  }
  return is_left_alligned(n) ? parent : climb(n);
}