#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <stdio.h>

typedef struct csv_line {
    char *col1;
    char *col2;
    char *col3;
    char *col4;
    char *col5;
} CSVLine;

/* Lit une ligne CSV.
   Retourne :
   1  → ligne lue
   0  → EOF
  -1  → erreur de format */
int csv_read_line(FILE *file, CSVLine *line);

/* Libère la mémoire associée à une ligne */
void csv_free_line(CSVLine *line);

#endif
