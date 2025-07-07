#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <stddef.h>

/* Levenshtein Distance - calculates minimum single-character edits */
int levenshtein_distance(const char *s1, const char *s2);

/* Damerau-Levenshtein Distance - includes transpositions */
int damerau_levenshtein_distance(const char *s1, const char *s2);

/* Jaro-Winkler Similarity - gives more weight to common prefixes */
double jaro_winkler_similarity(const char *s1, const char *s2);

/* Soundex - handles phonetic similarities */
void soundex(const char *str, char *code);
int soundex_similarity(const char *s1, const char *s2);

/* N-gram Similarity - compares character sequences */
double ngram_similarity(const char *s1, const char *s2, int n);

/* Longest Common Subsequence - finds shared character patterns */
int lcs_length(const char *s1, const char *s2);
double lcs_similarity(const char *s1, const char *s2);

/* Hybrid scoring - weighted combination of algorithms */
double calculate_similarity_score(const char *input, const char *command);

#endif