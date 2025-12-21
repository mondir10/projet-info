#include <stdio.h>
#include <string.h>

#include "histo/histogram.h"
#include "network/losses.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <csv_file> <max|src|real|loss>\n",
                argv[0]);
        return 1;
    }

    const char *csv = argv[1];
    const char *mode = argv[2];

    if (strcmp(mode, "max") == 0 ||
        strcmp(mode, "src") == 0 ||
        strcmp(mode, "real") == 0) {
        return compute_histogram(csv, mode);
    }

    if (strcmp(mode, "loss") == 0) {
        return compute_network_losses(csv, "losses.dat");
    }

    fprintf(stderr, "Mode invalide\n");
    return 1;
}
