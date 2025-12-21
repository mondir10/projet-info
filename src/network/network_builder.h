#ifndef NETWORK_BUILDER_H
#define NETWORK_BUILDER_H

#include "network.h"
#include "../avl/avl_tree.h"

/* Construit le graphe réseau depuis le CSV
   Retourne la racine de l'AVL contenant les Node* */
AVLNode *build_network_from_csv(const char *csv_path);

/* Libération complète */
void free_network(AVLNode *nodes);

#endif
