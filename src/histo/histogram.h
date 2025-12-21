#ifndef HISTOGRAM_H
#define HISTOGRAM_H

/* mode = "max" | "src" | "real"
   Retourne 0 si OK, >0 si erreur */
int compute_histogram(const char *csv_path, const char *mode);

#endif

