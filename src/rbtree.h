#ifndef RBTREE_H
#define RBTREE_H

enum rbt_color {
    RBT_RED,
    RBT_BLACK
};

typedef struct rbt_node rbt_node_t;
struct rbt_node {
    int data;
    enum rbt_color color;
    rbt_node_t* left;
    rbt_node_t* right;
};

typedef struct rbtree rbtree_t;
struct rbtree {
    rbt_node_t* node;
};

rbtree_t rbtree_init(void);
void rbtree_insert_node(rbtree_t tree[const static 1], const int data);
void rbtree_delete_node(rbtree_t tree[const static 1], const int data);
void rbtree_traverse_preorder(const rbtree_t tree[const static 1]);
void rbtree_traverse_inorder(const rbtree_t tree[const static 1]);
void rbtree_traverse_postorder(const rbtree_t tree[const static 1]);
void rbtree_delete(rbtree_t tree[const static 1]);

#endif

