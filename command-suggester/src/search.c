#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "utils.h"

/* Default search configuration */
search_config_t default_search_config = {
    .min_score_threshold = 0.1,
    .max_results = MAX_SUGGESTIONS,
    .levenshtein_weight = 0.25,
    .jaro_winkler_weight = 0.30,
    .soundex_weight = 0.15,
    .ngram_weight = 0.20,
    .lcs_weight = 0.10
};

/* Search for similar commands */
search_results_t *search_similar_commands(command_database_t *db, const char *input) {
    if (!db || !input) return NULL;
    
    search_results_t *results = safe_malloc(sizeof(search_results_t));
    results->count = 0;
    
    // Initialize with low scores
    for (int i = 0; i < MAX_SUGGESTIONS; i++) {
        results->results[i].score = -1.0;
    }
    
    database_iterator_t *iter = create_iterator(db);
    command_entry_t *entry;
    
    while ((entry = iterator_next(iter)) != NULL) {
        double score = calculate_similarity_score(input, entry->command);
        
        // Skip if score is below threshold
        if (score < default_search_config.min_score_threshold) {
            continue;
        }
        
        // Find insertion point (keep results sorted by score)
        int insert_pos = results->count;
        for (int i = 0; i < results->count; i++) {
            if (score > results->results[i].score) {
                insert_pos = i;
                break;
            }
        }
        
        // Insert if we have room or if it's better than the worst result
        if (results->count < MAX_SUGGESTIONS || insert_pos < MAX_SUGGESTIONS) {
            // Shift results to make room
            int shift_count = min(results->count - insert_pos, MAX_SUGGESTIONS - insert_pos - 1);
            if (shift_count > 0) {
                memmove(&results->results[insert_pos + 1], 
                        &results->results[insert_pos], 
                        shift_count * sizeof(search_result_t));
            }
            
            // Insert new result
            strncpy(results->results[insert_pos].command, entry->command, MAX_COMMAND_LENGTH - 1);
            results->results[insert_pos].command[MAX_COMMAND_LENGTH - 1] = '\0';
            
            strncpy(results->results[insert_pos].package, entry->package, MAX_PACKAGE_LENGTH - 1);
            results->results[insert_pos].package[MAX_PACKAGE_LENGTH - 1] = '\0';
            
            strncpy(results->results[insert_pos].version, entry->version, MAX_PACKAGE_LENGTH - 1);
            results->results[insert_pos].version[MAX_PACKAGE_LENGTH - 1] = '\0';
            
            results->results[insert_pos].score = score;
            
            if (results->count < MAX_SUGGESTIONS) {
                results->count++;
            }
        }
    }
    
    free_iterator(iter);
    return results;
}

/* Sort results by score (descending) */
void sort_results(search_results_t *results) {
    if (!results || results->count <= 1) return;
    
    // Simple bubble sort (sufficient for small arrays)
    for (int i = 0; i < results->count - 1; i++) {
        for (int j = 0; j < results->count - 1 - i; j++) {
            if (results->results[j].score < results->results[j + 1].score) {
                // Swap
                search_result_t temp = results->results[j];
                results->results[j] = results->results[j + 1];
                results->results[j + 1] = temp;
            }
        }
    }
}

/* Print suggestions in Ubuntu format */
void print_suggestions(const char *input, search_results_t *results) {
    if (!results || results->count == 0) {
        printf("Command '%s' not found.\n", input ? input : "");
        return;
    }
    
    printf("Command '%s' not found, did you mean:\n", input ? input : "");
    
    for (int i = 0; i < results->count; i++) {
        printf("  command '%s' from deb %s", 
               results->results[i].command,
               results->results[i].package);
        
        if (strlen(results->results[i].version) > 0) {
            printf(" (%s)", results->results[i].version);
        }
        printf("\n");
    }
    
    printf("Try: apt install <deb name>\n");
}

/* Free search results */
void free_search_results(search_results_t *results) {
    if (results) {
        free(results);
    }
}

/* Additional search functions for fine-tuning */

/* Search with custom configuration */
search_results_t *search_with_config(command_database_t *db, const char *input, search_config_t *config) {
    if (!db || !input || !config) return NULL;
    
    search_config_t old_config = default_search_config;
    default_search_config = *config;
    
    search_results_t *results = search_similar_commands(db, input);
    
    default_search_config = old_config;
    return results;
}

/* Get top N results */
search_results_t *get_top_results(search_results_t *results, int n) {
    if (!results || n <= 0) return NULL;
    
    search_results_t *top = safe_malloc(sizeof(search_results_t));
    top->count = min(results->count, n);
    
    for (int i = 0; i < top->count; i++) {
        top->results[i] = results->results[i];
    }
    
    return top;
}

/* Filter results by minimum score */
search_results_t *filter_by_score(search_results_t *results, double min_score) {
    if (!results) return NULL;
    
    search_results_t *filtered = safe_malloc(sizeof(search_results_t));
    filtered->count = 0;
    
    for (int i = 0; i < results->count; i++) {
        if (results->results[i].score >= min_score) {
            filtered->results[filtered->count++] = results->results[i];
        }
    }
    
    return filtered;
}

/* Get suggestions for prefix */
search_results_t *search_by_prefix(command_database_t *db, const char *prefix) {
    if (!db || !prefix) return NULL;
    
    search_results_t *results = safe_malloc(sizeof(search_results_t));
    results->count = 0;
    
    int prefix_len = strlen(prefix);
    database_iterator_t *iter = create_iterator(db);
    command_entry_t *entry;
    
    while ((entry = iterator_next(iter)) != NULL && results->count < MAX_SUGGESTIONS) {
        if (strncmp(entry->command, prefix, prefix_len) == 0) {
            strncpy(results->results[results->count].command, entry->command, MAX_COMMAND_LENGTH - 1);
            results->results[results->count].command[MAX_COMMAND_LENGTH - 1] = '\0';
            
            strncpy(results->results[results->count].package, entry->package, MAX_PACKAGE_LENGTH - 1);
            results->results[results->count].package[MAX_PACKAGE_LENGTH - 1] = '\0';
            
            strncpy(results->results[results->count].version, entry->version, MAX_PACKAGE_LENGTH - 1);
            results->results[results->count].version[MAX_PACKAGE_LENGTH - 1] = '\0';
            
            results->results[results->count].score = 1.0; // Perfect prefix match
            results->count++;
        }
    }
    
    free_iterator(iter);
    return results;
}

/* Print detailed results with scores (for debugging) */
void print_detailed_results(const char *input, search_results_t *results) {
    if (!results || results->count == 0) {
        printf("No suggestions found for '%s'\n", input ? input : "");
        return;
    }
    
    printf("Suggestions for '%s' (with scores):\n", input ? input : "");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < results->count; i++) {
        printf("%2d. %-20s (%.3f) from %s", 
               i + 1,
               results->results[i].command,
               results->results[i].score,
               results->results[i].package);
        
        if (strlen(results->results[i].version) > 0) {
            printf(" (%s)", results->results[i].version);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
}