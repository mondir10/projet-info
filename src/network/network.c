#include "network.h"
#include <stdlib.h>
#include <string.h>

/* -------- Création / destruction -------- */

Node *node_create(const char *id) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;

    n->id = strdup(id);
    n->edges = NULL;
    n->has_parent = 0;
    n->incoming = 0.0;
    n->loss = 0.0;
    n->next = NULL;

    return n;
}

void node_free(Node *node) {
    if (!node) return;

    Edge *e = node->edges;
    while (e) {
        Edge *tmp = e;
        e = e->next;
        free(tmp);
    }

    free(node->id);
    free(node);
}

/* -------- Arêtes -------- */

void node_add_edge(Node *from, Node *to, double volume, double loss_percent) {
    Edge *e = malloc(sizeof(Edge));
    if (!e) return;

    e->to = to;
    e->volume = volume;
    e->loss_percent = loss_percent;
    e->next = from->edges;
    from->edges = e;

    to->has_parent = 1;
}

/* -------- DFS de propagation -------- */

void compute_losses(Node *node, double incoming_volume) {
    if (!node) return;

    node->incoming += incoming_volume;

    for (Edge *e = node->edges; e; e = e->next) {
        double lost = e->volume * (e->loss_percent / 100.0);
        double out = e->volume - lost;

        node->loss += lost;
        compute_losses(e->to, out);
    }
}
