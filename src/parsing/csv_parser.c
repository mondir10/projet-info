#include "csv_parser.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char *dup_or_null(const char *s) {
    if (!s || strcmp(s, "-") == 0)
        return NULL;
    return strdup(s);
}

int csv_read_line(FILE *file, CSVLine *line) {
    char buffer[BUFFER_SIZE];

    if (!fgets(buffer, BUFFER_SIZE, file))
        return 0;  // EOF

    char *cols[5] = {NULL, NULL, NULL, NULL, NULL};
    char *token;
    char *saveptr;
    int col = 0;

    token = strtok_r(buffer, ";\n", &saveptr);
    while (token && col < 5) {
        cols[col++] = token;
        token = strtok_r(NULL, ";\n", &saveptr);
    }

    if (col != 5)
        return -1;

    line->col1 = dup_or_null(cols[0]);
    line->col2 = dup_or_null(cols[1]);
    line->col3 = dup_or_null(cols[2]);
    line->col4 = dup_or_null(cols[3]);
    line->col5 = dup_or_null(cols[4]);

    return 1;
}

void csv_free_line(CSVLine *line) {
    free(line->col1);
    free(line->col2);
    free(line->col3);
    free(line->col4);
    free(line->col5);
}

