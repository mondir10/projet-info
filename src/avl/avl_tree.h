#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_node {
    char *key;
    void *data;
    int height;
    struct avl_node *left;
    struct avl_node *right;
} AVLNode;

AVLNode *avl_insert(AVLNode *root, char *key, void *data);
void *avl_find(AVLNode *root, const char *key);
void avl_free(AVLNode *root, void (*free_data)(void *));

#endif
