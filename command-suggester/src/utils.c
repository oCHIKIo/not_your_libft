#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/stat.h>
#include "utils.h"

/* String utilities */
char *str_tolower(char *str) {
    if (!str) return NULL;
    
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

char *str_trim(char *str) {
    if (!str) return NULL;
    
    // Trim leading whitespace
    char *start = str;
    while (isspace(*start)) start++;
    
    // Trim trailing whitespace
    char *end = start + strlen(start) - 1;
    while (end > start && isspace(*end)) end--;
    *(end + 1) = '\0';
    
    // Move trimmed string to beginning if needed
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
    
    return str;
}

int str_isempty(const char *str) {
    return !str || !*str;
}

char *str_duplicate(const char *str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char *copy = safe_malloc(len + 1);
    strcpy(copy, str);
    return copy;
}

/* Math utilities */
int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

double min_double(double a, double b) {
    return (a < b) ? a : b;
}

double max_double(double a, double b) {
    return (a > b) ? a : b;
}

/* Memory utilities */
void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *safe_calloc(size_t count, size_t size) {
    void *ptr = calloc(count, size);
    if (!ptr) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* File utilities */
int file_exists(const char *filename) {
    struct stat st;
    return stat(filename, &st) == 0;
}

long file_size(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1;
    
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

char *read_file_line(FILE *fp, char *buffer, size_t size) {
    if (!fp || !buffer) return NULL;
    return fgets(buffer, size, fp);
}

/* Debug utilities */
void debug_print(const char *format, ...) {
    #ifdef DEBUG
    va_list args;
    va_start(args, format);
    printf("[DEBUG] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
    #endif
}

void print_separator(const char *title) {
    printf("\n=== %s ===\n", title);
}