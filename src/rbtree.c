#include "rbtree.h"

rbtree_t rbtree_init(void)
{
    return (rbtree_t){.node = NULL};
}

void rbtree_insert_node(rbtree_t tree[const static 1], const int data)
{

}

void rbtree_delete_node(rbtree_t tree[const static 1], const int data)
{

}

void rbtree_traverse_preorder_helper(const rbt_node_t* const node)
{
    if (node == NULL) {
        return;
    }
    printf("%d\n", node->data);
    rbtree_traverse_preorder_helper(node->left);
    rbtree_traverse_preorder_helper(node->right);
}

void rbtree_traverse_preorder(const rbtree_t tree[const static 1])
{
    rbtree_traverse_preorder_helper(tree->node);
}

void rbtree_traverse_inorder_helper(const rbt_node_t* const node)
{
    if (node == NULL) {
        return;
    }
    rbtree_traverse_preorder_helper(node->left);
    printf("%d\n", node->data);
    rbtree_traverse_preorder_helper(node->right);
}

void rbtree_traverse_inorder(const rbtree_t tree[const static 1])
{
    rbtree_traverse_inorder_helper(tree->node);
}

void rbtree_traverse_postorder_helper(const rbt_node_t* const node)
{
    if (node == NULL) {
        return;
    }
    rbtree_traverse_preorder_helper(node->left);
    rbtree_traverse_preorder_helper(node->right);
    printf("%d\n", node->data);
}

void rbtree_traverse_postorder(const rbtree_t tree[const static 1])
{
    rbtree_traverse_postorder_helper(tree->node);
}

void rbtree_delete_helper(rbt_node_t* const node)
{
    if (node == NULL) {
        return;
    }
    rbtree_delete_helper(node->left);
    rbtree_delete_helper(node->right);
    free(node);
}

void rbtree_delete(rbtree_t tree[const static 1])
{
    rbtree_delete_helper(tree->node);
}
