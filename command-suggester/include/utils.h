#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/* String utilities */
char *str_tolower(char *str);
char *str_trim(char *str);
int str_isempty(const char *str);
char *str_duplicate(const char *str);

/* Math utilities */
int min(int a, int b);
int max(int a, int b);
int min3(int a, int b, int c);
double min_double(double a, double b);
double max_double(double a, double b);

/* Memory utilities */
void *safe_malloc(size_t size);
void *safe_calloc(size_t count, size_t size);

/* File utilities */
int file_exists(const char *filename);
long file_size(const char *filename);
char *read_file_line(FILE *fp, char *buffer, size_t size);

/* Debug utilities */
void debug_print(const char *format, ...);
void print_separator(const char *title);

#endif