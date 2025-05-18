struct node {
  node* left = nullptr;
  node* right = nullptr;
  unsigned height = 0;
};

void compute_height(node*);

inline void leaf_height(node* n) {
  n->height = 0;
}

inline void left_height(node* n) {
  compute_height(n->left);
  n->height = n->left->height + 1;
}

inline void right_height(node* n) {
  compute_height(n->right);
  n->height = n->right->height + 1;
}

inline void mountain_height(node* n) {
  auto& [left, right, height] = *n;
  compute_height(left);
  compute_height(right);

  height = left->height >= right->height ? left->height + 1 : right->height + 1;
}

void compute_height(node* n) {
  auto& [left, right, _] = *n;
  !left && !right  ? leaf_height(n)
  : left && !right ? left_height(n)
  : !left && right ? right_height(n)
                   : mountain_height(n);
}