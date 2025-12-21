#include "losses.h"
#include "network_builder.h"
#include "network.h"

#include <stdio.h>
#include <stdlib.h>

/* Écriture AVL -> fichier */
static void write_losses(FILE *out, AVLNode *node) {
    if (!node) return;

    write_losses(out, node->left);

    Node *n = (Node *)node->data;
    fprintf(out, "%s;%.3f\n", n->id, n->loss / 1000.0);

    write_losses(out, node->right);
}

int compute_network_losses(const char *csv_path,
                           const char *output_dat) {

    AVLNode *nodes = build_network_from_csv(csv_path);
    if (!nodes) return 1;

    /* Lancer DFS depuis les racines */
    void traverse_roots(AVLNode *root) {
        if (!root) return;

        traverse_roots(root->left);

        Node *n = (Node *)root->data;
        if (!n->has_parent) {
            compute_losses(n, 0.0);
        }

        traverse_roots(root->right);
    }

    traverse_roots(nodes);

    /* Écriture fichier */
    FILE *out = fopen(output_dat, "w");
    if (!out) {
        perror("fopen");
        free_network(nodes);
        return 2;
    }

    fprintf(out, "identifier;loss(M.m3)\n");
    write_losses(out, nodes);

    fclose(out);
    free_network(nodes);
    return 0;
}
