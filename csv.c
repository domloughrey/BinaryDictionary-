#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "csv.h"

// Helper Functions

// Function to parse long double
long double parse_ld_or_zero(const char *s) {
    while (*s && isspace((unsigned char)*s)) s++;
    if (*s == '\0') return 0.0L;

    char *end = NULL;
    long double v = strtold(s, &end);

    while (end && *end && isspace((unsigned char)*end)) end++;
    return (end && *end == '\0') ? v : 0.0L;
}

// Split a line by commas into FIELD_MAX strings.
int line_split(char *line, char out[FIELD_MAX][STRLEN]) {
    int f = 0;
    char *p = line;
    while (f < FIELD_MAX) {
        char *comma = strchr(p, ',');
        size_t len = (comma ? (size_t)(comma - p) : strlen(p));
        if (len >= STRLEN) len = STRLEN - 1;                        
        memcpy(out[f], p, len);
        out[f][len] = '\0';
        f++;
        if (!comma) break;
        p = comma + 1;
    }
    // if line ended early, pad with empty strings
    while (f < FIELD_MAX) {
        out[f][0] = '\0';
        f++;
    }
    return FIELD_MAX;
}
