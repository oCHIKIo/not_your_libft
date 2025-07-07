#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "similarity.h"
#include "utils.h"

/* Levenshtein Distance - calculates minimum single-character edits */
int levenshtein_distance(const char *s1, const char *s2) {
    if (!s1 || !s2) return -1;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;
    
    // Create matrix
    int **matrix = safe_malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        matrix[i] = safe_malloc((len2 + 1) * sizeof(int));
    }
    
    // Initialize first row and column
    for (int i = 0; i <= len1; i++) matrix[i][0] = i;
    for (int j = 0; j <= len2; j++) matrix[0][j] = j;
    
    // Fill matrix
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
            matrix[i][j] = min3(
                matrix[i-1][j] + 1,      // deletion
                matrix[i][j-1] + 1,      // insertion
                matrix[i-1][j-1] + cost  // substitution
            );
        }
    }
    
    int result = matrix[len1][len2];
    
    // Free matrix
    for (int i = 0; i <= len1; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return result;
}

/* Damerau-Levenshtein Distance - includes transpositions */
int damerau_levenshtein_distance(const char *s1, const char *s2) {
    if (!s1 || !s2) return -1;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;
    
    // Create matrix
    int **matrix = safe_malloc((len1 + 2) * sizeof(int *));
    for (int i = 0; i <= len1 + 1; i++) {
        matrix[i] = safe_malloc((len2 + 2) * sizeof(int));
    }
    
    int maxdist = len1 + len2;
    matrix[0][0] = maxdist;
    
    for (int i = 0; i <= len1; i++) {
        matrix[i+1][0] = maxdist;
        matrix[i+1][1] = i;
    }
    for (int j = 0; j <= len2; j++) {
        matrix[0][j+1] = maxdist;
        matrix[1][j+1] = j;
    }
    
    for (int i = 1; i <= len1; i++) {
        int db = 0;
        for (int j = 1; j <= len2; j++) {
            int k = db;
            int l = 0;
            if (s1[i-1] == s2[j-1]) {
                l = 0;
                db = j;
            } else {
                l = 1;
            }
            
            // Find last occurrence of s2[j-1] in s1[0..i-1]
            for (int m = i-1; m >= 1; m--) {
                if (s1[m-1] == s2[j-1]) {
                    k = m;
                    break;
                }
            }
            
            matrix[i+1][j+1] = min3(
                matrix[i][j] + l,           // substitution
                matrix[i+1][j] + 1,         // insertion
                matrix[i][j+1] + 1          // deletion
            );
            
            if (k > 0 && l > 0) {
                matrix[i+1][j+1] = min(matrix[i+1][j+1], 
                    matrix[k][l] + (i-k-1) + 1 + (j-l-1)); // transposition
            }
        }
    }
    
    int result = matrix[len1+1][len2+1];
    
    // Free matrix
    for (int i = 0; i <= len1 + 1; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return result;
}

/* Helper function for Jaro similarity */
static double jaro_similarity(const char *s1, const char *s2) {
    if (!s1 || !s2) return 0.0;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 == 0 && len2 == 0) return 1.0;
    if (len1 == 0 || len2 == 0) return 0.0;
    
    int match_window = max(len1, len2) / 2 - 1;
    if (match_window < 0) match_window = 0;
    
    int *s1_matches = safe_calloc(len1, sizeof(int));
    int *s2_matches = safe_calloc(len2, sizeof(int));
    
    int matches = 0;
    int transpositions = 0;
    
    // Find matches
    for (int i = 0; i < len1; i++) {
        int start = max(0, i - match_window);
        int end = min(i + match_window + 1, len2);
        
        for (int j = start; j < end; j++) {
            if (s2_matches[j] || s1[i] != s2[j]) continue;
            s1_matches[i] = s2_matches[j] = 1;
            matches++;
            break;
        }
    }
    
    if (matches == 0) {
        free(s1_matches);
        free(s2_matches);
        return 0.0;
    }
    
    // Find transpositions
    int k = 0;
    for (int i = 0; i < len1; i++) {
        if (!s1_matches[i]) continue;
        while (!s2_matches[k]) k++;
        if (s1[i] != s2[k]) transpositions++;
        k++;
    }
    
    free(s1_matches);
    free(s2_matches);
    
    return ((double)matches / len1 + (double)matches / len2 + 
            (double)(matches - transpositions/2) / matches) / 3.0;
}

/* Jaro-Winkler Similarity - gives more weight to common prefixes */
double jaro_winkler_similarity(const char *s1, const char *s2) {
    if (!s1 || !s2) return 0.0;
    
    double jaro = jaro_similarity(s1, s2);
    if (jaro < 0.7) return jaro;
    
    // Calculate common prefix length (up to 4 characters)
    int prefix = 0;
    for (int i = 0; i < min(min(strlen(s1), strlen(s2)), 4); i++) {
        if (s1[i] == s2[i]) {
            prefix++;
        } else {
            break;
        }
    }
    
    return jaro + (0.1 * prefix * (1.0 - jaro));
}

/* Soundex - handles phonetic similarities */
void soundex(const char *str, char *code) {
    if (!str || !code) return;
    
    const char *mapping = "01230120022455012623010202";
    // A=0, B=1, C=2, D=3, E=0, F=1, G=2, H=0, I=0, J=2, K=2, L=4, M=5, N=5, 
    // O=0, P=1, Q=2, R=6, S=2, T=3, U=0, V=1, W=0, X=2, Y=0, Z=2
    
    // Initialize code
    code[0] = code[1] = code[2] = code[3] = '0';
    code[4] = '\0';
    
    if (strlen(str) == 0) return;
    
    // First character is always uppercase letter
    code[0] = toupper(str[0]);
    
    char prev = '0';
    int pos = 1;
    
    for (int i = 1; str[i] && pos < 4; i++) {
        char c = toupper(str[i]);
        if (c >= 'A' && c <= 'Z') {
            char digit = mapping[c - 'A'];
            if (digit != '0' && digit != prev) {
                code[pos++] = digit;
            }
            prev = digit;
        }
    }
}

int soundex_similarity(const char *s1, const char *s2) {
    char code1[5], code2[5];
    soundex(s1, code1);
    soundex(s2, code2);
    return strcmp(code1, code2) == 0;
}

/* N-gram Similarity - compares character sequences */
double ngram_similarity(const char *s1, const char *s2, int n) {
    if (!s1 || !s2 || n <= 0) return 0.0;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 < n && len2 < n) {
        return (strcmp(s1, s2) == 0) ? 1.0 : 0.0;
    }
    
    if (len1 < n || len2 < n) return 0.0;
    
    int ngrams1 = len1 - n + 1;
    int ngrams2 = len2 - n + 1;
    int common = 0;
    
    // Count common n-grams
    for (int i = 0; i < ngrams1; i++) {
        for (int j = 0; j < ngrams2; j++) {
            if (strncmp(s1 + i, s2 + j, n) == 0) {
                common++;
                break; // Count each n-gram only once
            }
        }
    }
    
    return (2.0 * common) / (ngrams1 + ngrams2);
}

/* Longest Common Subsequence - finds shared character patterns */
int lcs_length(const char *s1, const char *s2) {
    if (!s1 || !s2) return 0;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 == 0 || len2 == 0) return 0;
    
    // Create matrix
    int **matrix = safe_malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        matrix[i] = safe_calloc(len2 + 1, sizeof(int));
    }
    
    // Fill matrix
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i-1] == s2[j-1]) {
                matrix[i][j] = matrix[i-1][j-1] + 1;
            } else {
                matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
            }
        }
    }
    
    int result = matrix[len1][len2];
    
    // Free matrix
    for (int i = 0; i <= len1; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return result;
}

double lcs_similarity(const char *s1, const char *s2) {
    if (!s1 || !s2) return 0.0;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 == 0 && len2 == 0) return 1.0;
    if (len1 == 0 || len2 == 0) return 0.0;
    
    int lcs_len = lcs_length(s1, s2);
    return (2.0 * lcs_len) / (len1 + len2);
}

/* Hybrid scoring - weighted combination of algorithms */
double calculate_similarity_score(const char *input, const char *command) {
    if (!input || !command) return 0.0;
    
    // Convert to lowercase for comparison
    char *input_lower = str_duplicate(input);
    char *command_lower = str_duplicate(command);
    str_tolower(input_lower);
    str_tolower(command_lower);
    
    double score = 0.0;
    
    // Exact match gets maximum score
    if (strcmp(input_lower, command_lower) == 0) {
        score = 1.0;
    } else {
        // Calculate individual scores
        int lev_dist = levenshtein_distance(input_lower, command_lower);
        double jaro_winkler = jaro_winkler_similarity(input_lower, command_lower);
        int soundex_match = soundex_similarity(input_lower, command_lower);
        double ngram_2 = ngram_similarity(input_lower, command_lower, 2);
        double ngram_3 = ngram_similarity(input_lower, command_lower, 3);
        double lcs_sim = lcs_similarity(input_lower, command_lower);
        
        // Normalize Levenshtein distance
        int max_len = max(strlen(input_lower), strlen(command_lower));
        double lev_sim = 1.0 - (double)lev_dist / max_len;
        
        // Weighted combination
        score = 0.25 * lev_sim +           // Levenshtein
                0.30 * jaro_winkler +      // Jaro-Winkler (higher weight)
                0.15 * soundex_match +     // Soundex
                0.15 * ngram_2 +           // 2-gram
                0.10 * ngram_3 +           // 3-gram
                0.05 * lcs_sim;            // LCS
        
        // Boost for prefix matches
        if (strncmp(input_lower, command_lower, min(strlen(input_lower), 3)) == 0) {
            score *= 1.2;
        }
        
        // Boost for short commands
        if (strlen(command_lower) <= 4) {
            score *= 1.1;
        }
    }
    
    free(input_lower);
    free(command_lower);
    
    return min_double(score, 1.0); // Cap at 1.0
}