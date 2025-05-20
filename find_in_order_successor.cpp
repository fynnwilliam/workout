struct node {
  node* parent = nullptr;
  node* left = nullptr;
  node* right = nullptr;
  int value = 0;
};

constexpr bool operator>(const node& lhs, const node& rhs) noexcept {
  return lhs.value > rhs.value;
}

node* leftmost_key(node& n) {
  return n.left ? leftmost_key(*n.left) : &n;
}

node* root_node(node& n) {
  return n.parent ? root_node(*n.parent) : &n;
}

bool is_left_alligned(node& n) {
  auto& [parent, _, _, _] = n;
  return parent && &n == parent->left;
}

node* climb(node& n) {
  node* root = root_node(n);
  return *root > n ? root : nullptr;
}

node* in_order_successor(node& n) {
  auto& [parent, _, right, _] = n;
  node* u = right ? leftmost_key(*right) : &n;

  if (u == &n) {
    return is_left_alligned(n) ? parent : climb(n);
  }

  return u;
}