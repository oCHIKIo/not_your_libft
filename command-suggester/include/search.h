#ifndef SEARCH_H
#define SEARCH_H

#include "database.h"
#include "similarity.h"

#define MAX_SUGGESTIONS 15

/* Search result structure */
typedef struct {
    char command[MAX_COMMAND_LENGTH];
    char package[MAX_PACKAGE_LENGTH];
    char version[MAX_PACKAGE_LENGTH];
    double score;
} search_result_t;

/* Search results container */
typedef struct {
    search_result_t results[MAX_SUGGESTIONS];
    int count;
} search_results_t;

/* Search engine functions */
search_results_t *search_similar_commands(command_database_t *db, const char *input);
void sort_results(search_results_t *results);
void print_suggestions(const char *input, search_results_t *results);
void print_detailed_results(const char *input, search_results_t *results);
void free_search_results(search_results_t *results);

/* Search configuration */
typedef struct {
    double min_score_threshold;
    int max_results;
    double levenshtein_weight;
    double jaro_winkler_weight;
    double soundex_weight;
    double ngram_weight;
    double lcs_weight;
} search_config_t;

extern search_config_t default_search_config;

#endif