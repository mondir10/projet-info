#include "avl_tree.h"
#include <stdlib.h>
#include <string.h>

/* --------- Utils --------- */

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static int height(AVLNode *n) {
    return n ? n->height : 0;
}

static AVLNode *create_node(char *key, void *data) {
    AVLNode *node = malloc(sizeof(AVLNode));
    if (!node) return NULL;

    node->key = key;
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static int balance_factor(AVLNode *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

/* --------- Rotations --------- */

static AVLNode *rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static AVLNode *rotate_left(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

/* --------- Insertion --------- */

AVLNode *avl_insert(AVLNode *root, char *key, void *data) {
    if (!root)
        return create_node(key, data);

    int cmp = strcmp(key, root->key);

    if (cmp < 0)
        root->left = avl_insert(root->left, key, data);
    else if (cmp > 0)
        root->right = avl_insert(root->right, key, data);
    else {
        root->data = data;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balance_factor(root);

    if (balance > 1 && strcmp(key, root->left->key) < 0)
        return rotate_right(root);

    if (balance < -1 && strcmp(key, root->right->key) > 0)
        return rotate_left(root);

    if (balance > 1 && strcmp(key, root->left->key) > 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && strcmp(key, root->right->key) < 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

/* --------- Search --------- */

void *avl_find(AVLNode *root, const char *key) {
    if (!root) return NULL;

    int cmp = strcmp(key, root->key);
    if (cmp == 0) return root->data;
    if (cmp < 0) return avl_find(root->left, key);
    return avl_find(root->right, key);
}

/* --------- Free --------- */

void avl_free(AVLNode *root, void (*free_data)(void *)) {
    if (!root) return;

    avl_free(root->left, free_data);
    avl_free(root->right, free_data);

    if (free_data)
        free_data(root->data);

    free(root->key);
    free(root);
}
