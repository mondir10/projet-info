#ifndef LOSSES_H
#define LOSSES_H

#include "../avl/avl_tree.h"

/* Calcule les pertes et écrit un fichier .dat */
int compute_network_losses(const char *csv_path,
                           const char *output_dat);

#endif
