node* leftmost_key(node* n)
{
    return n->left ? leftmost_key(n->left) : n;
}

node* root_node(node* n)
{
    return n->parent ? root_node(n->parent) : n;
}

bool is_left_alligned(node* n)
{
    return n == n->parent->left;
}

node* climb(node* n)
{
    node* root{root_node(n)};
    return *root > *n ? root : nullptr;
}

node* in_order_successor(node* n)
{
    if (!n) return nullptr;
    
    node* u = !n->right ? n : leftmost_key(n->right);
    
    if (u == n)
    {
        return is_left_alligned(n) ? n->parent : climb(n);
    }
    else return u;
}