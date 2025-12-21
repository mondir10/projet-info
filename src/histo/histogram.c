#include "histogram.h"
#include "../parsing/csv_parser.h"
#include "../avl/avl_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct factory {
    char *id;
    double max_capacity;
    double source_volume;
    double real_volume;
} Factory;

/* -------- Utils -------- */

static Factory *factory_create(const char *id) {
    Factory *f = malloc(sizeof(Factory));
    if (!f) return NULL;

    f->id = strdup(id);
    f->max_capacity = 0.0;
    f->source_volume = 0.0;
    f->real_volume = 0.0;
    return f;
}

static void free_factory(void *data) {
    Factory *f = data;
    free(f->id);
    free(f);
}

/* -------- Écriture AVL en ordre inverse -------- */

static void write_reverse(FILE *out, AVLNode *root, const char *mode) {
    if (!root) return;

    write_reverse(out, root->right, mode);

    Factory *f = root->data;
    if (strcmp(mode, "max") == 0)
        fprintf(out, "%s;%.3f\n", f->id, f->max_capacity / 1000.0);
    else if (strcmp(mode, "src") == 0)
        fprintf(out, "%s;%.3f\n", f->id, f->source_volume / 1000.0);
    else if (strcmp(mode, "real") == 0)
        fprintf(out, "%s;%.3f\n", f->id, f->real_volume / 1000.0);
}

int compute_histogram(const char *csv_path, const char *mode) {
    FILE *file = fopen(csv_path, "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    AVLNode *factories = NULL;
    CSVLine line;
    int ret;

    while ((ret = csv_read_line(file, &line)) == 1) {

        /* Ligne USINE seule → capacité max */
        if (line.col2 && !line.col3 && line.col4) {
            Factory *f = avl_find(factories, line.col2);
            if (!f) {
                f = factory_create(line.col2);
                factories = avl_insert(factories, strdup(line.col2), f);
            }
            f->max_capacity = atof(line.col4);
        }

        /* Ligne SOURCE → USINE */
        if (!line.col1 && line.col2 && line.col3 && line.col4 && line.col5) {
            Factory *f = avl_find(factories, line.col3);
            if (!f) {
                f = factory_create(line.col3);
                factories = avl_insert(factories, strdup(line.col3), f);
            }

            double vol = atof(line.col4);
            double leak = atof(line.col5) / 100.0;

            f->source_volume += vol;
            f->real_volume += vol * (1.0 - leak);
        }

        csv_free_line(&line);
    }

    fclose(file);

    if (ret == -1) {
        fprintf(stderr, "Erreur de parsing CSV\n");
        avl_free(factories, free_factory);
        return 2;
    }

    char filename[64];
    snprintf(filename, sizeof(filename), "histo_%s.dat", mode);

    FILE *out = fopen(filename, "w");
    if (!out) {
        perror("fopen");
        avl_free(factories, free_factory);
        return 3;
    }

    fprintf(out, "identifier;value(M.m3)\n");
    write_reverse(out, factories, mode);

    fclose(out);
    avl_free(factories, free_factory);
    return 0;
}

