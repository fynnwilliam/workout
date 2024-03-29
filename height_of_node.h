void compute_height(node*);

inline void leaf_height(node* n)
{
    n->height = 0;
}

inline void left_height(node* n)
{
    compute_height(n->left);
    n->height = n->left->height + 1;
}

inline void right_height(node* n)
{
    compute_height(n->right);
    n->height = n->right->height + 1;
}

inline void mountain_height(node* n)
{
    compute_height(n->left);
    compute_height(n->right);
    
    n->height = n->left->height >= n->right->height ? n->left->height + 1 : n->right->height + 1;
}

void compute_height(node* n)
{
    !n->left && !n->right ? leaf_height(n)  :
     n->left && !n->right ? left_height(n)  :
    !n->left &&  n->right ? right_height(n) : mountain_height(n);
}