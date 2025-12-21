#include "network_builder.h"
#include "../parsing/csv_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Callback pour free AVL */
static void free_node_cb(void *data) {
    node_free((Node *)data);
}

AVLNode *build_network_from_csv(const char *csv_path) {
    FILE *file = fopen(csv_path, "r");
    if (!file) {
        perror("fopen");
        return NULL;
    }

    AVLNode *nodes = NULL;
    CSVLine line;

    while (csv_read_line(file, &line) == 1) {

        /* Connexion réseau : parent -> enfant */
        if (!line.col1 && line.col2 && line.col3 && line.col4 && line.col5) {

            /* parent */
            Node *parent = avl_find(nodes, line.col2);
            if (!parent) {
                parent = node_create(line.col2);
                nodes = avl_insert(nodes, strdup(line.col2), parent);
            }

            /* enfant */
            Node *child = avl_find(nodes, line.col3);
            if (!child) {
                child = node_create(line.col3);
                nodes = avl_insert(nodes, strdup(line.col3), child);
            }

            double volume = atof(line.col4);
            double loss = atof(line.col5);

            node_add_edge(parent, child, volume, loss);
        }

        csv_free_line(&line);
    }

    fclose(file);
    return nodes;
}

void free_network(AVLNode *nodes) {
    avl_free(nodes, free_node_cb);
}
