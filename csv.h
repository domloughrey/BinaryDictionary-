#ifndef _CSV_H
#define _CSV_H

#define FIELD_MAX 35
#define STRLEN    128
#define LINE_MAX  1024

long double parse_ld_or_zero(const char *s);
int line_split(char *line, char out[FIELD_MAX][STRLEN]);

#endif
