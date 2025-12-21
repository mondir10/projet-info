#ifndef NETWORK_H
#define NETWORK_H

#include <stddef.h>

/* Arête du graphe */
typedef struct edge {
    struct node *to;
    double volume;
    double loss_percent;
    struct edge *next;
} Edge;

/* Nœud du réseau */
typedef struct node {
    char *id;
    Edge *edges;
    int has_parent;

    /* calculs */
    double incoming;
    double loss;

    struct node *next; /* pour liste éventuelle */
} Node;

/* Création / destruction */
Node *node_create(const char *id);
void node_free(Node *node);

/* Arêtes */
void node_add_edge(Node *from, Node *to, double volume, double loss_percent);

/* Calcul DFS */
void compute_losses(Node *node, double incoming_volume);

#endif
